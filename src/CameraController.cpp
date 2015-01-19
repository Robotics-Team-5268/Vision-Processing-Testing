#include "WPILib.h"
#include "RobotParam.h"
#include <cmath>

class CameraController {

	struct Scores{
		double rectangularity;
		double aspectRatioVert;
		double aspectRatioHorz;
	};

	struct TargetReport {
		int vertIndex;
		int horzIndex;
		bool hot; //or naaaah
		double totalScore;
		double leftScore;
		double rightScore;
		double tapeWidthScore;
		double vertScore;
	};

public:
	ColorImage *frame;
	AxisCamera *camera;

	Threshold threshold = (60, 100, 90, 255, 20, 255);
	ParticleFilterCriteria2 criteria[] = {IMAQ_MT_AREA, AREA_MINIMUM, AREA_MAXIMUM, false, false};

	Scores scores[];

	TargetReport target;

	CameraController() {
		// create an image
		frame = imaqCreateImage(IMAQ_IMAGE_RGB, 0);

		// open the camera at the IP address assigned. This is the IP address that the camera
		// can be accessed through the web interface.
		camera = new AxisCamera(CAMERA_IP);
	}

	void update(){
		// grab an image, draw the circle, and provide it for the camera server which will
		// in turn send it to the dashboard.

		camera->GetImage(frame);

		//Apply the threshold
		BinaryImage *thresholdImage = frame->ThresholdHSV(threshold);

		//Apply a convex
		BinaryImage *convexHullImage = thresholdImage->ConvexHull(false);

		//apply the particle filter
		BinaryImage *filteredImage = convexHullImage->ParticleFilter(criteria, 1);

		//Scores
		std::vector<ParticleAnalysisReport> *reports = filteredImage->GetOrderedParticleAnalysisReports();
		scores = new Scores[reports->size()];

		for(unsigned i = 0; i < reports->size(); i++){
			ParticleAnalysisReport *report = &(reports->at(i));

			scores[i].rectangularity = scoreRectangularity(report);
			scores[i].aspectRatioVert = scoreAspectRatio(filteredImage, report, true);
			scores[i].aspectRatioHorz = scoreAspectRatio(filteredImage, report, false);

			if(scoreCompare(scores[i], false))
			{
				printf("Particle: %d is a High Goal  centerX: %f centerY: %f \n", i, report->center_mass_x_normalized, report->center_mass_y_normalized);
				printf("Distance: %f \n", computeDistance(thresholdImage, report));
			} else if (scoreCompare(scores[i], true)){
				printf("Particle: %d is a Middle Goal  centerX: %f centerY: %f \n", i, report->center_mass_x_normalized, report->center_mass_y_normalized);
				printf("Distance: %f \n", computeDistance(thresholdImage, report));
			} else {
				printf("Particle: %d is not a goal  centerX: %f centerY: %f \n", i, report->center_mass_x_normalized, report->center_mass_y_normalized);
			}
			printf("Rect: %f  ARinner: %f \n", scores[i].rectangularity, scores[i].aspectRatioHorz);
			printf("ARouter: %f", scores[i].aspectRatioVert);
		}

		target.totalScore = target.leftScore = target.rightScore = target.tapeWidthScore = target.vertScore = 0;
		target.vertIndex = verticalTargets[0];
	}

private:
	double scoreAspectRatio(BinaryImage *image, ParticleAnalysisReport *report, bool vert)
	{
		double rectLong, rectShort, idealAspectRatio, aspectRatio;
		idealAspectRatio = vert ? (4.0/32) : (23.5/4); //Vert reflector 4" wide x 32" tall, horizontal 23.5" wide x 4" tall

		imaqMeasureParticle(image->GetImaqImage(), report->particleIndex, 0, IMAQ_MT_EQUIVALENT_RECT_LONG_SIDE, &rectLong);
		imaqMeasureParticle(image->GetImaqImage(), report->particleIndex, 0, IMAQ_MT_EQUIVALENT_RECT_SHORT_SIDE, &rectShort);

		//Divide width by height to measure aspect ratio
		if(report->boundingRect.width > report->boundingRect.height){
			//particle is wider than it is tall, divide long by short
			aspectRatio = ratioToScore(((rectLong/rectShort)/idealAspectRatio));
		} else {
			//particle is taller than it is wide, divide short by long
			aspectRatio = ratioToScore(((rectShort/rectLong)/idealAspectRatio));
		}
		return aspectRatio;		//force to be in range 0-100
	}

	double ratioToScore(double ratio)
	{
		return (std::max<double>(0, std::min<double>(100*(1-fabs(1-ratio)), 100)));
	}

	double scoreRectangularity(ParticleAnalysisReport *report)
	{
		if(report->boundingRect.width*report->boundingRect.height !=0){
			return 100*report->particleArea/(report->boundingRect.width*report->boundingRect.height);
		}else{
			return 0;
		}
	}

	bool scoreCompare(Scores scores, bool vert)
	{
		bool isTarget = true;

		isTarget &= scores.rectangularity > RECT_LIMIT;
		if(vert){
			isTarget &= scores.aspectRatioVert > ASPECT_RATIO_LIMIT;
		}else{
			isTarget &= scores.aspectRatioHorz > ASPECT_RATIO_LIMIT;
		}

		return isTarget;
	}

	double computeDistance (BinaryImage *image, ParticleAnalysisReport *report){
		double rectLong, height;
		int targetHeight;

		imaqMeasureParticle(image->GetImaqImage(), report->particleIndex, 0, IMAQ_MT_EQUIVALENT_RECT_LONG_SIDE, &rectLong);

		height = std::min<double>(report->boundingRect.height, rectLong);
		targetHeight = 32;

		return Y_IMAGE_RES * targetHeight / (height * 12 * 2 * tan(VIEW_ANGLE*PI/(180*2)));
	}

};
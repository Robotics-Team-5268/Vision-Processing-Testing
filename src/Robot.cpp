#include "WPILib.h"
#include "RobotParam.h"
#include "CameraController.cpp"

class Robot: public IterativeRobot
{
private:

	LiveWindow *lw;

	CameraController *ccontroller;

	void RobotInit()
	{
		lw = LiveWindow::GetInstance();

		ccontroller = new CameraController();
	}

	void AutonomousInit()
	{

	}

	void AutonomousPeriodic()
	{

	}

	void TeleopInit()
	{

	}

	void TeleopPeriodic()
	{

		ccontroller->update();
	}

	void TestPeriodic()
	{
		lw->Run();
	}
};

START_ROBOT_CLASS(Robot);

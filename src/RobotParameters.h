#ifndef ROBOT_PARAMETERS_H
#define ROBOT_PARAMETERS_H
#include "WPILib.h"
#include "RobotBase.h"
#include "RobotParameters.h"

/* Uncomment as needed (make sure to update ports
#define GATE_BUTTON 5 //LB top trigger
#define GATE_SOLENOID_ONE 8
#define GATE_SOLENOID_TWO 6
#define ARM_BUTTON_UP 6 //RB top trigger
#define ARM_BUTTON_DOWN 5 //to be found out
#define ARM_SOLENOID 2
#define ArmUpAxes 3
#define ArmDownAxes 3
#define DriveAxesUpDown 2
#define DriveAxesLeftRight 1
#define PistonButton 1
#define ARM_1_MOTOR_CHANNEL 3
#define ARM_1_HI_SWITCH 13
#define ARM_1_LO_SWITCH 14
#define SCOOPER_UP_BUTTON 2
#define SCOOPER_DOWN_BUTTON 3
#define SCOOPER_STAY_UP 4
#define SCOOPER_STAY_DOWN 1
#define COMP_LIMIT_SWITCH	6		// compressor stuff
#define COMP_RELAY_CHANNEL	7		// more compressor stuff
#define ULTRASONIC_INPUT_CHANNEL 2
#define TOGGLE_DRIVE_BUTTON 8
#define FORWARD_LIGHT_SOL 3
#define BACK_LIGHT_SOL 4
#define GYRO_CHANNEL 1
*/
#define CAMERAMOTOR_LR 2 // Port 2 for the left right pivot motor for camera (I can haz left?)
#define CAMERAMOTOR_UD 3 // Port 3 for the up down pivot motor for camera (I can haz up?)

// camera constants used for distance calculation
#define Y_IMAGE_RES 480 // x image reslolution in pixels, should be 120, 240 or 480
#define VIEW_ANGLE 49 // axis mM1013
// #define VIEW_ANGLE 48 // acis 206 camera
// #define VIEW_ANGLE 43.5  // Axis m1011 camera
#define PI 3.142592653

// score limits used ofr target identificaion
#define RECT_LIMIT 40
#define ASPECT_RATIO_LIMIT 55

// Score limits used for hot target determination
#define TAPE_WIDTH_LIMIT 50
#define VERTICAL_SCORE_LIMIT 50
#define LR_SCORE_LIMIT 50

// MINIMUM OIF PARTICLES TO BE CONSIDERED
#define AREA_MINIMUM 150
#define AREA_MAXIMUM 65535


// MAXIMUM NNUMBER OF PARTICLES TO PROCESS
#define MAX_PARTICLES 8

// THRESHHOLD VALUES
#define MIN_H 137
#define MAX_H 154
#define MIN_S 36
#define MAX_S 93
#define MIN_V 232
#define MAX_V 250

//OTHER
#define CAMERA_IP "10.52.68.11"



#endif

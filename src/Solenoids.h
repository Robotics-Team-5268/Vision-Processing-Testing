#include "WPILib.h"
#include "RobotParameters.h"


typedef enum ArmCommandType
{
ArmDown, ArmUp
};


class Arm
{
public:

Solenoid *sol;

explicit Arm() { sol = new Solenoid( ARM_SOLENOID ); }

void ArmCommand( ArmCommandType command )
{
switch(command)
{
case ArmUp:
sol->Set( true );
break;
case ArmDown:
sol->Set( false );
break;
}

}
void ArmTeleOpPeriodic( Joystick * js )
{
	if (js->GetRawButton ( ARM_BUTTON_UP ) )
	{
		ArmCommand (ArmUp);
	}
	if (js->GetRawButton ( ARM_BUTTON_DOWN ) )
	{
		ArmCommand (ArmUp);
	}
}
};



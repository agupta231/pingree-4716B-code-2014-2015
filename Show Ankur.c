#pragma config(Motor,  port2,           driveLeft,     tmotorVex393, openLoop, reversed)
#pragma config(Motor,  port3,           driveRight,    tmotorVex393, openLoop)
#pragma config(Motor,  port4,           builder,       tmotorVex393, openLoop)
#pragma config(Motor,  port5,           cube,          tmotorVex393, openLoop)
#pragma config(Motor,  port6,           liftLeftTop,   tmotorVex393, openLoop, reversed)
#pragma config(Motor,  port7,           liftLeftBack,  tmotorVex393, openLoop, reversed)
#pragma config(Motor,  port8,           liftRightTop,  tmotorVex393, openLoop)
#pragma config(Motor,  port9,           liftRightBack, tmotorVex393, openLoop)
#pragma platform(VEX)

//Competition Control and Duration Settings
#pragma competitionControl(Competition)
#pragma autonomousDuration(20)
#pragma userControlDuration(120)

#include "Vex_Competition_Includes.c"   //Main competition background code...do not modify!

void pre_auton()
{
  // Set bStopTasksBetweenModes to false if you want to keep user created tasks running between
  // Autonomous and Tele-Op modes. You will need to manage all user created tasks if set to false.
  bStopTasksBetweenModes = true;

	// All activities that occur before the competition starts
	// Example: clearing encoders, setting servo positions, ...
}

//////////////////////////////// YAY FUNCTIONS ////////////////////////////////////////////

void drive(int power) {
	motor[driveLeft] = power;
	motor[driveRight] = power;
}

void driveTrainLeft(int power) {
	motor[driveLeft] = power;
}


void driveTrainRight(int power) {
	motor[driveRight] = power;
}


void lift(int power) {
	motor[liftLeftBack] = power;
	motor[liftLeftTop] = power;
	motor[liftRightTop] = power;
	motor[liftRightBack] = power;
}

void builderClaw(int power) {
	motor[builder] = power;
}

void cubeClaw(int power) {
	motor[cube] = power;
}

float changeMode(float currentMode) {
	float newMode;
	if(currentMode == .9) {
		newMode =  .3;
	}
	else if(currentMode == .3) {
		newMode =  .9;
	}
	return newMode;
}

/////////////////////////////////////////////////////////////////////////////////////////////////

task autonomous()
{
	drive(-127);
	wait1Msec(500);
}

task usercontrol()
{
	int joy_right;
	int joy_left;
	float mode = 0.9;

	while (true)
	{
		joy_right = (vexRT[Ch2]) * mode;
		joy_left = (vexRT[Ch3]) * mode;

		if(vexRT[Btn6U] == 1) {
			lift(127);

			driveTrainLeft(joy_left);
			driveTrainRight(joy_right);
		}
		else if(vexRT[Btn6D] == 1) {
			lift(-127);

			driveTrainLeft(joy_left);
			driveTrainRight(joy_right);
		}
		else {
			lift(0);
		}

		//Cube Claw if statements
		//To open
		if(vexRT[Btn8U] == 1) {
			cubeClaw(127);

			driveTrainLeft(joy_left);
			driveTrainRight(joy_right);
		}
		//to close
		else if(vexRT[Btn8D] == 1) {
			cubeClaw(-127);

			driveTrainLeft(joy_left);
			driveTrainRight(joy_right);
		}
		else {
			cubeClaw(0);
		}

		//Builder Claw if statements
		//to open
		if(vexRT[Btn8L] == 1) {
			builderClaw(127);

			driveTrainLeft(joy_left);
			driveTrainRight(joy_right);
		}
		//to close
		else if(vexRT[Btn8R] == 1) {
			builderClaw(-127);

			driveTrainLeft(joy_left);
			driveTrainRight(joy_right);
		}
		else {
			builderClaw(0);
		}

		if (vexRT[Btn7D] == 1) {
			mode = changeMode(mode);
		}

		driveTrainLeft(joy_left);
		driveTrainRight(joy_right);

		wait1Msec(10);
	}
}

#pragma config(Sensor, dgtl1,  limitSwitch,    sensorTouch)
#pragma config(Motor,  port2,           driveRight,    tmotorVex393, openLoop, reversed)
#pragma config(Motor,  port3,           driveLeft,     tmotorVex393, openLoop)
#pragma config(Motor,  port4,           builder,       tmotorVex393, openLoop)
#pragma config(Motor,  port5,           cube,          tmotorVex393, openLoop)
#pragma config(Motor,  port6,           liftLeftTop,   tmotorVex393, openLoop, reversed)
#pragma config(Motor,  port7,           liftLeftBack,  tmotorVex393, openLoop, reversed)
#pragma config(Motor,  port8,           liftRightTop,  tmotorVex393, openLoop)
#pragma config(Motor,  port9,           liftRightBack, tmotorVex393, openLoop)
//*!!Code automatically generated by 'ROBOTC' configuration wizard               !!*//

#pragma platform(VEX)

//Competition Control and Duration Settings
#pragma competitionControl(Competition)
#pragma autonomousDuration(20)
#pragma userControlDuration(120)

#include "Vex_Competition_Includes.c"   //Main competition background code...do not modify!

/////////////////////////////// Pre-Auton Functions //////////////////////////////

const short leftButton = 1;
const short centerButton = 2;
const short rightButton = 4;

int userChoice;

void waitForPress() {
	while(nLCDButtons == 0) {}
	wait1Msec(5);
}

void waitForRelease() {
	while(nLCDButtons != 0) {}
	wait1Msec(5);
}

/////////////////////////////// End Functions ////////////////////////////////////

void pre_auton()
{
  bStopTasksBetweenModes = true;

  bLCDBacklight = true;
  clearLCDLine(0);
  clearLCDLine(1);

  displayLCDCenteredString(0, "Powered by 4716B");
  displayLCDCenteredString(1, "R | E | B");

  while(nLCDButtons != centerButton) {
  	if(nLCDButtons == leftButton) {
  		while(true) {
			displayLCDCenteredString(1, "R | L");
			if(nLCDButtons == leftButton) {
				userChoice = 1;
			}
			else if(nLCDButtons == rightButton) {
				userChoice = 2;
			}
			else if(nLCDButtons == centerButton) {
				break;
			}
		}
  		break;
  	}
  	else if(nLCDButtons == rightButton) {
  		while(true) {
			displayLCDCenteredString(1, "R | L");
			if(nLCDButtons == leftButton) {
				userChoice = 3;
			}
			else if(nLCDButtons == rightButton) {
				userChoice = 4;
			}
			else if(nLCDButtons == centerButton) {
				break;
			}
		}
  		break;
  	}
  	else if(nLCDButtons == centerButton) {
  		userChoice = 0;
  		break;
  	}
  }

  clearLCDLine(0);
  clearLCDLine(1);

  displayLCDCenteredString(0, "4716B God Team");
}

//////////////////////////////// YAY FUNCTIONS ////////////////////////////////////////////
void displayBatterys() {
	string mainBattery,
				 backupBattery;

	displayLCDString(0, 0, "Primary: ");
	sprintf(mainBattery, "%1.2f%c", nImmediateBatteryLevel/1000.0,'V'); //Build the value to be displayed
	displayNextLCDString(mainBattery);

	displayLCDString(1, 0, "Backup: ");
	sprintf(backupBattery, "%1.2f%c", BackupBatteryLevel/1000.0, 'V');	//Build the value to be displayed
	displayNextLCDString(backupBattery);
}

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

void builderClaw(int power, bool enabled) {
	if(enabled == true) {
		if(power == 0) {
			motor[builder] = power;
		}
		else if(power > 0) {
			if(SensorValue(limitSwitch) != 1) {
				motor[builder] = power;
			}
			else {
				motor[builder] = 0;
			}
		}
		else if(power < 0) {
			motor[builder] = power;
		}
	}
	else {
		motor[builder] = power;
	}
}

bool changeBuilderClawMode(bool currentMode) {
	bool newMode;
	if(currentMode == true) {
		newMode = false;
	}
	else if(currentMode == false) {
		newMode = true;
	}
	return newMode;
}

void cubeClaw(int power) {
	motor[cube] = power;
}

int changeMode(int currentMode) {
	int newMode;
	if(currentMode == 1) {
		newMode =  -1;
	}
	else if(currentMode == -1) {
		newMode =  1;
	}
	return newMode;
}

float assignController (int currentController, int currentMode) {
	float reassignment;

	if(currentController == 0) {
		if(currentMode == 1) {
			reassignment = vexRT[Ch2];
		}
		else if(currentMode == -1) {
			reassignment = -(vexRT[Ch3]);
		}
	}
	else if(currentController == 1) {
		if(currentMode == 1) {
			reassignment = vexRT[Ch3];
		}
		else if(currentMode == -1) {
			reassignment = -(vexRT[Ch2]);
		}
	}

	return reassignment;
}

float changeSpeed(float currentSpeed) {
	float newSpeed;

	if(currentSpeed == 1.0) {
		newSpeed = 0.3;
	}
	else if(currentSpeed == 0.3) {
		newSpeed = 1.0;
	}
	return newSpeed;
}

void frontFacingClaw(int power, int mode, bool clawMode) {
	if(mode == 1) {
		cubeClaw(power);
	}
	else if(mode == -1) {
		builderClaw(power, clawMode);
	}
}

void rearFacingClaw(int power, int mode, bool clawMode) {
	if(mode == 1) {
		builderClaw(power, clawMode);
	}
	else if(mode == -1) {
		cubeClaw(power);
	}
}

/////////////////////////////////////////////////////////////////////////////////////////////////

task autonomous()
{
	switch(userChoice) {
		case 1:
			drive(-127);
			wait1Msec(500);
			drive(0);
			wait1Msec(50);
			break;
		case 2:
			drive(-127);
			wait1Msec(500);
			drive(0);
			wait1Msec(50);
			break;
		case 3:
			break;
		case 4:
			break;
		default:
			break;
	}
}

/////////////////////////////////////////////////////////////////////////////////////////////////

task usercontrol()
{
	float joy_right;
	float joy_left;
	int mode = 1;
	float speed = 1.0;
	bool builderLimitSwitchEnabled = true;

	while (true)
	{
		// 0 for right, 1 for left
		joy_right = assignController(0, mode) * speed;
		joy_left = assignController(1, mode) * speed;

		if(nLCDButtons == centerButton) {
			displayBatterys();
		}
		else {
			displayLCDCenteredString(0, "4617B God Team");
			clearLCDLine(1);
		}

		if(vexRT[Btn5U] == 1) {
			lift(127);

			driveTrainLeft(joy_left);
			driveTrainRight(joy_right);
		}
		else if(vexRT[Btn5D] == 1) {
			lift(-127);

			driveTrainLeft(joy_left);
			driveTrainRight(joy_right);
		}
		else {
			lift(0);
		}
		//Cube Claw if statements
		//To open

		if(vexRT[Btn6D] == 1) {
			frontFacingClaw(-127, mode, builderLimitSwitchEnabled);
		}
		else if(vexRT[Btn6U] == 1) {
			frontFacingClaw(127, mode, builderLimitSwitchEnabled);
		}
		else {
			frontFacingClaw(0, mode, builderLimitSwitchEnabled);
		}

		if(vexRT[Btn8D] == 1) {
			rearFacingClaw(-127, mode, builderLimitSwitchEnabled);
		}
		else if(vexRT[Btn8U] == 1) {
			rearFacingClaw(127, mode, builderLimitSwitchEnabled);
		}
		else {
			rearFacingClaw(0, mode, builderLimitSwitchEnabled);
		}

		if (vexRT[Btn7L] == 1) {
			motor[driveLeft] = 0;
			motor[driveRight] = 0;
			wait1Msec(100);

			speed = changeSpeed(speed);

			motor[driveLeft] = 0;
			motor[driveRight] = 0;
			wait1Msec(100);
		}
		if (vexRT[Btn7D] == 1) {
			motor[driveLeft] = 0;
			motor[driveRight] = 0;
			wait1Msec(100);

			mode = changeMode(mode);

			motor[driveLeft] = 0;
			motor[driveRight] = 0;
			wait1Msec(100);
		}
		if (vexRT[Btn7U] == 1) {
			motor[driveLeft] = 0;
			motor[driveRight] = 0;
			builderClaw(0, builderLimitSwitchEnabled);
			wait1Msec(100);

			builderLimitSwitchEnabled = changeBuilderClawMode(builderLimitSwitchEnabled);

			builderClaw(0, builderLimitSwitchEnabled);
			motor[driveLeft] = 0;
			motor[driveRight] = 0;
			wait1Msec(100);
		}

		driveTrainLeft(joy_left);
		driveTrainRight(joy_right);

		wait1Msec(10);
	}
}

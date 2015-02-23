#pragma config(UART_Usage, UART2, uartVEXLCD, baudRate19200, IOPins, None, None)
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
  displayLCDCenteredString(1, "Goal | Exit | Load");

  while(nLCDButtons != centerButton) {
  	if(nLCDButtons == leftButton) {
			userChoice = 1;
  		break;
  	}
  	else if(nLCDButtons == centerButton) {
  		userChoice = 0;
  		break;
  	}
  	else if(nLCDButtons == rightButton) {
  		userChoice = 2;
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

void builderClaw(int power) {
	motor[builder] = power;
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

int assignController (int currentController, int currentMode) {
	int reassignment;

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

/////////////////////////////////////////////////////////////////////////////////////////////////

task autonomous()
{
	switch(userChoice) {
		case 1:
			//Goalside Code
			break;
		case 2:
			//Loaderside code
			break;
		default:
			break;
	}
}

task usercontrol()
{
	int joy_right;
	int joy_left;
	int mode = 1;

	while (true)
	{
		// 0 for right, 1 for left
		joy_right = assignController(0, mode);
		joy_left = assignController(1, mode);

		if(nLCDButtons == centerButton) {
			displayBatterys();
		}
		else {
			displayLCDCenteredString(0, "4617B God Team");
			clearLCDLine(1);
		}

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
			motor[driveLeft] = 0;
			motor[driveRight] = 0;
			wait1Msec(100);

			mode = changeMode(mode);

			motor[driveLeft] = 0;
			motor[driveRight] = 0;
			wait1Msec(100);
		}

		driveTrainLeft(joy_left);
		driveTrainRight(joy_right);

		wait1Msec(10);
	}
}
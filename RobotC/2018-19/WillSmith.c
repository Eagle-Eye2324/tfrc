#pragma config(I2C_Usage, I2C1, i2cSensors)
#pragma config(Sensor, dgtl1,  BallistaAxis,   sensorQuadEncoder)
#pragma config(Sensor, dgtl3,  BallistaFire,   sensorQuadEncoder)
#pragma config(Sensor, dgtl5,  AutonomousModeSwitch, sensorTouch)
#pragma config(Sensor, I2C_1,  LeftDrive,      sensorQuadEncoderOnI2CPort,    , AutoAssign )
#pragma config(Sensor, I2C_2,  RightDrive,     sensorQuadEncoderOnI2CPort,    , AutoAssign )
#pragma config(Motor,  port1,           LMDrive,       tmotorVex393_HBridge, openLoop, driveLeft, encoderPort, I2C_1)
#pragma config(Motor,  port2,           RMDrive,       tmotorVex393_MC29, openLoop, reversed, driveRight, encoderPort, I2C_2)
#pragma config(Motor,  port3,           LRFDrive,      tmotorVex393_MC29, openLoop, driveLeft)
#pragma config(Motor,  port4,           RRFDrive,      tmotorVex393_MC29, openLoop, driveRight)
#pragma config(Motor,  port5,           LRRDrive,      tmotorVex393_MC29, openLoop, reversed, driveLeft)
#pragma config(Motor,  port6,           RRRDrive,      tmotorVex393_MC29, openLoop, reversed, driveRight)
#pragma config(Motor,  port7,           BallistaFire,  tmotorVex393_MC29, openLoop, encoderPort, dgtl1)
#pragma config(Motor,  port8,           BallIntake,    tmotorVex393_MC29, openLoop)
#pragma config(DatalogSeries, 0, "Main Battery Level", Properties, immediateBatteryLevel, , 50)
#pragma config(DatalogSeries, 1, "Backup Battery Level", Properties, BackupBatteryLevel, , 50)
//*!!Code automatically generated by 'ROBOTC' configuration wizard               !!*//

/*---------------------------------------------------------------------------*/
/*                                                                           */
/*                         VEXnet Joystick Weirdness                         */
/*                                                                           */
/*	So the joysticks on the VEXnet controller are labled weirdly.  Because   */
/*	of this, keep the following in mind when progamming it.  Up and down on  */
/*	the right stick is channel 1.  Left and right on the right stick is      */
/*	channel 0.  Up and down on the left stick is channel 2, and left and     */
/*	right on the left stick is channel 3.  If you are having problems with   */
/*	controls, make sure that you have the channels set correctly!  If you    */
/*	mess up, it's entirely your fault!                                       */
/* 		- Robbie                                                               */
/*                                                                           */
/*---------------------------------------------------------------------------*/

/*---------------------------------------------------------------------------*/
/*                                                                           */
/*                             Sensor Notes                                  */
/*                                                                           */
/*	 - Shaft Encoders > 360 counts per revolution (1 count = 1 degree)       */
/*	 - IMEs > 627.2 counts per revolution (1.74222222222 = 1 degree)         */
/*                                                                           */
/*---------------------------------------------------------------------------*/

/*---------------------------------------------------------------------------*/
/*                                                                           */
/*                             Motor Names                                   */
/*                                                                           */
/*	Drive Motors                                                             */
/*		LMDrive > Left Middle Drive Motor                                      */
/*		RMDrive > Right Middle Drive Motor                                     */
/*		LRFDrive > Left Rear Front Drive Motor                                 */
/*		RRFDrive > Right Rear Front Drive Motor                                */
/*		LRRDrive > Left Rear Rear Drive Motor                                  */
/*		RRRDrive > Right Rear Rear Drive Motor                                 */
/*	                                                                         */
/*	Other Motors                                                             */
/*		BallistaFire > Actuates the firing mechanism for the ballista          */
/*		BallIntake > Two motors, connected with a Y-cable.  Powers the ball    */
/*			intake system.                                                       */
/*                                                                           */
/*---------------------------------------------------------------------------*/

/*---------------------------------------------------------------------------*/
/*                                                                           */
/*        Description: Competition template for VEX EDR                      */
/*                                                                           */
/*---------------------------------------------------------------------------*/

// This code is for the VEX cortex platform
#pragma platform(VEX2)

// Select Download method as "competition"
#pragma competitionControl(Competition)

// Main competition background code...do not modify!
#include "Vex_Competition_Includes.c"

/*---------------------------------------------------------------------------*/
/*                                                                           */
/*                     Variable and Function Definitions                     */
/*                                                                           */
/*---------------------------------------------------------------------------*/

//int ballistaPosition = 0;
bool firing = false;
bool fireBtnPressed = false;
bool intakeOn = false;
bool intakeBtnPressed = false;

/*---------------------------------------------------------------------------*/
/*                          Pre-Autonomous Functions                         */
/*                                                                           */
/*  You may want to perform some actions before the competition starts.      */
/*  Do them in the following function.  You must return from this function   */
/*  or the autonomous and usercontrol tasks will not be started.  This       */
/*  function is only called once after the cortex has been powered on and    */
/*  not every time that the robot is disabled.                               */
/*                                                                           */
/*---------------------------------------------------------------------------*/

void pre_auton()
{
  resetMotorEncoder(LMDrive);
  resetMotorEncoder(RMDrive);
	//resetMotorEncoder(BallistaAxis);

  bStopTasksBetweenModes = true;
}

/*---------------------------------------------------------------------------*/
/*                                                                           */
/*                              Autonomous Task                              */
/*                                                                           */
/*  This task is used to control your robot during the autonomous phase of   */
/*  a VEX Competition.                                                       */
/*                                                                           */
/*  You must modify the code to add your own robot specific commands here.   */
/*                                                                           */
/*---------------------------------------------------------------------------*/

task autonomous()
{
	motor[BallIntake] = 127;
	float pos = getMotorEncoder(port2);
	while (getMotorEncoder(port2) < pos + 327.9968024703564)
	{
		motor[LMDrive] = 127;
		motor[RMDrive] = 127;
		motor[LRRDrive] = 127;
		motor[LRFDrive] = 127;
		motor[RRRDrive] = 127;
		motor[RRFDrive] = 127;
	}
	motor[LMDrive] = 0;
	motor[RMDrive] = 0;
	motor[LRRDrive] = 0;
	motor[LRFDrive] = 0;
	motor[RRRDrive] = 0;
	motor[RRFDrive] = 0;
  if (SensorValue[AutonomousModeSwitch] == 1)
  {
  	pos = getMotorEncoder(port2);
  	while (getMotorEncoder(port2) < pos + 125.75359521624250763410040501014)
		{
			motor[LMDrive] = -127;
			motor[RMDrive] = 127;
			motor[LRRDrive] = -127;
			motor[LRFDrive] = -127;
			motor[RRRDrive] = 127;
			motor[RRFDrive] = 127;
		}
		pos = getMotorEncoder(port1);
		while (getMotorEncoder(port1) < pos + 418.2489511180865)
		{
			motor[LMDrive] = 127;
			motor[RMDrive] = 127;
			motor[LRRDrive] = 127;
			motor[LRFDrive] = 127;
			motor[RRRDrive] = 127;
			motor[RRFDrive] = 127;
		}
		sleep(1000);
		motor[BallIntake] = 0;
		pos = getMotorEncoder(port2);
		while (getMotorEncoder(port2) > pos - 418.2489511180865)
		{
			motor[LMDrive] = -127;
			motor[RMDrive] = -127;
			motor[LRRDrive] = -127;
			motor[LRFDrive] = -127;
			motor[RRRDrive] = -127;
			motor[RRFDrive] = -127;
		}
		pos = getMotorEncoder(port1);
  	while (getMotorEncoder(port1) > pos - 125.75359521624250763410040501014)
		{
			motor[LMDrive] = 127;
			motor[RMDrive] = -127;
			motor[LRRDrive] = 127;
			motor[LRFDrive] = 127;
			motor[RRRDrive] = -127;
			motor[RRFDrive] = -127;
		}
  }
  else
  {
		pos = getMotorEncoder(port2);
  	while (getMotorEncoder(port2) > pos - 125.75359521624250763410040501014)
		{
			motor[LMDrive] = 127;
			motor[RMDrive] = -127;
			motor[LRRDrive] = 127;
			motor[LRFDrive] = 127;
			motor[RRRDrive] = -127;
			motor[RRFDrive] = -127;
		}
		pos = getMotorEncoder(port1);
		while (getMotorEncoder(port1) < pos + 418.2489511180865)
		{
			motor[LMDrive] = 127;
			motor[RMDrive] = 127;
			motor[LRRDrive] = 127;
			motor[LRFDrive] = 127;
			motor[RRRDrive] = 127;
			motor[RRFDrive] = 127;
		}
		sleep(1000);
		motor[BallIntake] = 0;
		pos = getMotorEncoder(port2);
		while (getMotorEncoder(port2) > pos - 418.2489511180865)
		{
			motor[LMDrive] = -127;
			motor[RMDrive] = -127;
			motor[LRRDrive] = -127;
			motor[LRFDrive] = -127;
			motor[RRRDrive] = -127;
			motor[RRFDrive] = -127;
		}
		pos = getMotorEncoder(port1);
  	while (getMotorEncoder(port1) < pos + 125.75359521624250763410040501014)
		{
			motor[LMDrive] = -127;
			motor[RMDrive] = 127;
			motor[LRRDrive] = -127;
			motor[LRFDrive] = -127;
			motor[RRRDrive] = 127;
			motor[RRFDrive] = 127;
		}
	}
	// Move into position to fire a ball, and fire a ball, then move into position
	// to fire a second ball and fire a second ball
	AutonomousCodePlaceholderForTesting();
}

/*---------------------------------------------------------------------------*/
/*                                                                           */
/*                              User Control Task                            */
/*                                                                           */
/*  This task is used to control your robot during the user control phase of */
/*  a VEX Competition.                                                       */
/*                                                                           */
/*  You must modify the code to add your own robot specific commands here.   */
/*                                                                           */
/*---------------------------------------------------------------------------*/

task usercontrol()
{
  while (true)
  {
  	// Left side drive motors
  	motor[LMDrive] = vexRT[2];
  	motor[LRFDrive] = vexRT[2];
  	motor[LRRDrive] = vexRT[2];


  	// Right side drive motors
  	motor[RMDrive] = vexRT[1];
  	motor[RRFDrive] = vexRT[1];
  	motor[RRRDrive] = vexRT[1];

/*
  	// Ballista Positioning
  	if (vexRT[Btn6U] == 1 && ballistaPosition == 0)
  	{
  		float pos = SensorValue[BallistaAxis]
			while (SensorValue[BallistaAxis] < pos+n)
			{
				motor[BallistaAxis] = 127;
			}
			motor[BallistaAxis] = 0;
			ballistaPosition = 1;
  	}
  	if (vexRT[Btn6D] == 1 && ballistaPosition == 1)
  	{
  		float pos = SensorValue[BallistaAxis];
			while (SensorValue[BallistaAxis] > pos-n)
			{
				motor[BallistaAxis] = -127;
			}
			motor[BallistaAxis] = 0;
			ballistaPosition = 1;
  	}
*/

		// Ballista firing mechanism
		if (vexRT[Btn5U] == 1)
  	{
  		fireBtnPressed = true;
  	}
  	if (vexRT[Btn5U] == 0 && fireBtnPressed == true)
  	{
  		fireBtnPressed = false;
  		if (firing == true)
  		{
  			motor[BallistaFire] = 0;
  			firing = false;
  		}
  		else
  		{
  			motor[BallistaFire] = 127;
  			firing = true;
  		}
  	}

  	// Ball intake toggle
  	if (vexRT[Btn5D] == 1)
  	{
  		intakeBtnPressed = true;
  	}
  	if (vexRT[Btn5D] == 0 && intakeBtnPressed == true)
  	{
  		intakeBtnPressed = false;
  		if (intakeOn == true)
  		{
  			motor[BallIntake] = 0;
  			intakeOn = false;
  		}
  		else
  		{
  			motor[BallIntake] = 127;
  			intakeOn = true;
  		}
  	}
  }
}

/*----------------------------------------------------------------------------*/
/*                                                                            */
/*    Module:       main.cpp                                                  */
/*    Author:       VEX                                                       */
/*    Created:      Thu Sep 26 2019                                           */
/*    Description:  Competition Template                                      */
/*                                                                            */
/*----------------------------------------------------------------------------*/

// :: means it's an enum

// ---- START VEXCODE CONFIGURED DEVICES ----
// Robot Configuration:
// [Name]               [Type]        [Port(s)]
// LRDrive              motor         1               
// RRDrive              motor         10              
// LFDrive              motor         11              
// RFDrive              motor         20              
// Controller1          controller                    
// armExtMotor          motor         4               
// armUpMotor1          motor         3               
// clawMotor            motor         15              
// armUpMotor2          motor         5               
// Controller2          controller                    
// ---- END VEXCODE CONFIGURED DEVICES ----

#include "vex.h"
#include <stdio.h>
#include "callbacks.h"

using namespace vex;

// A global instance of competition
competition Competition;

// define your global instances of motors and other devices here

// define your variables here
bool armExtPressed;
bool armUpPressed;
bool clawOpen = false;
bool clawBtnPressed;

/*---------------------------------------------------------------------------*/
/*                          Pre-Autonomous Functions                         */
/*                                                                           */
/*  You may want to perform some actions before the competition starts.      */
/*  Do them in the following function.  You must return from this function   */
/*  or the autonomous and usercontrol tasks will not be started.  This       */
/*  function is only called once after the V5 has been powered on and        */
/*  not every time that the robot is disabled.                               */
/*---------------------------------------------------------------------------*/

void pre_auton(void) {
  // Initializing Robot Configuration. DO NOT REMOVE!
  vexcodeInit();

  // Reset all encoders
  LRDrive.resetRotation();
  LFDrive.resetRotation();
  RFDrive.resetRotation();
  RRDrive.resetRotation();
  armExtMotor.resetRotation();
  armUpMotor1.resetRotation();
  armUpMotor2.resetRotation();
  clawMotor.resetRotation();

  Brain.Screen.clearLine();
  // check what method of match control if any is being used
  if (Competition.isCompetitionSwitch()) {
      // connected to a competition switch
      Brain.Screen.print("Connected to a competition switch");
      printf("Connected to a competition switch");
  } else if (Competition.isFieldControl()) {
      // connected to a field control system
      Brain.Screen.print("Connected to a field control system");
      printf("Connected to a field control system");
  } else {
      // not connected to any control system
      Brain.Screen.print("not connected to a control system");
      printf("not connected to a control system");
  }

  armExtMotor.setVelocity(50, percent);
  armUpMotor1.setVelocity(50, percent);
  armUpMotor2.setVelocity(50, percent);
  armUpMotor1.setBrake(brakeType::hold);
  armUpMotor2.setBrake(brakeType::hold);
  armUpMotor1.setStopping(brakeType::hold);
  armUpMotor2.setStopping(brakeType::hold);
  clawMotor.setStopping(brakeType::hold);
}

/*---------------------------------------------------------------------------*/
/*                                                                           */
/*                              Autonomous Task                              */
/*                                                                           */
/*  This task is used to control your robot during the autonomous phase of   */
/*  a VEX Competition.                                                       */
/*                                                                           */
/*  You must modify the code to add your own robot specific commands here.   */
/*---------------------------------------------------------------------------*/

void autonomous(void) {
  // ..........................................................................
  // Insert autonomous user code here.
  // ..........................................................................
  // clear the screen in order to print the capacity and temperature
  Brain.Screen.clearScreen();
  // display the current battery capacity in percent
  Brain.Screen.setCursor(1, 20);
  Brain.Screen.print("Brain Battery Capacity: %d%%", Brain.Battery.capacity());
  // display the current battery temperature in percent
  Brain.Screen.setCursor(1, 40);
  Brain.Screen.print("Brain Battery Temperature: %d%%", Brain.Battery.temperature());
  
  // Print the battery capacity to the controller screen
  Controller1.Screen.clearScreen();
  Controller1.Screen.setCursor(1, 20);
  Controller1.Screen.print("Brain Battery Capacity: %d%%", Brain.Battery.capacity());
}

/*---------------------------------------------------------------------------*/
/*                                                                           */
/*                              User Control Task                            */
/*                                                                           */
/*  This task is used to control your robot during the user control phase of */
/*  a VEX Competition.                                                       */
/*                                                                           */
/*  You must modify the code to add your own robot specific commands here.   */
/*---------------------------------------------------------------------------*/

void usercontrol(void) {
  // User control code here, inside the loop
  while (1) {
    // This is the main execution loop for the user control program.
    // Each time through the loop your program should update motor + servo
    // values based on feedback from the joysticks.

    // Diagnostic stuff
    Controller1.Screen.clearScreen();
    Controller1.Screen.setCursor(1, 1);
    Controller1.Screen.print("Brain Battery Capacity: %d%%", Brain.Battery.capacity());
    Controller1.Screen.setCursor(2, 1);
    Controller1.Screen.print("armUpMotor1: %d%%", armUpMotor1.position(degrees));
    Controller1.Screen.setCursor(3, 1);
    Controller1.Screen.print("armUpMotor2: %d%%", armUpMotor2.position(degrees));
    Controller1.Screen.setCursor(4, 1);
    Controller1.Screen.print("armExtMotor: %d%%", armExtMotor.position(degrees));
    Controller1.Screen.setCursor(5, 1);
    Controller1.Screen.print("clawMotor: %d%%", clawMotor.position(degrees));

    /*=============================User control start============================*/

    /*---------------------------------------------------------------------------*/
    /*                             Drive motor control                           */
    /*---------------------------------------------------------------------------*/

    RFDrive.spin(directionType::fwd, Controller1.Axis3.position()/2.5, percentUnits::pct);
    RRDrive.spin(directionType::fwd, Controller1.Axis3.position()/2.5, percentUnits::pct);
    LFDrive.spin(directionType::fwd, Controller1.Axis2.position()/2.5, percentUnits::pct);
    LRDrive.spin(directionType::fwd, Controller1.Axis2.position()/2.5, percentUnits::pct);


    /*---------------------------------------------------------------------------*/
    /*                           Arm extenstion control                          */
    /*---------------------------------------------------------------------------*/

    if (Controller2.Axis3.value() == 0)
    {
      armExtMotor.stop();
    }
    if (armExtMotor.position(degrees) <= 570 && Controller2.Axis3.value() > 0)
    {
      armExtMotor.spin(forward, Controller2.Axis3.value(), percent);
    } else {
      armExtMotor.stop();
    }
    if (armExtMotor.position(degrees) >= 0 && Controller2.Axis3.value() < 0)
    {
      armExtMotor.spin(forward, Controller2.Axis3.value(), percent);
    } else {
      armExtMotor.stop();
    }


    /*---------------------------------------------------------------------------*/
    /*                           Arm elevation control                           */
    /*---------------------------------------------------------------------------*/

    if (armExtMotor.position(degrees) >= 70)
    {
      if (armUpMotor1.position(degrees) <= 500 && Controller2.Axis2.value() > 0)
      {
        armUpMotor1.spin(forward, Controller2.Axis2.value()/2, percent);
        armUpMotor2.spin(forward, Controller2.Axis2.value()/2, percent);
      } else {
        if (Controller2.Axis2.value() == 0)
        {
          armUpMotor1.stop();
          armUpMotor2.stop();
        }
      }
    } else {
      if (armUpMotor1.position(degrees) <= 300 && Controller2.Axis2.value() > 0)
      {
        armUpMotor1.spin(forward, Controller2.Axis2.value()/2, percent);
        armUpMotor2.spin(forward, Controller2.Axis2.value()/2, percent);
      } else {
        if (Controller2.Axis2.value() == 0)
        {
          armUpMotor1.stop();
          armUpMotor2.stop();
        }
      }
    }
    if (armUpMotor1.position(degrees) >= 0 && Controller2.Axis2.value() < 0)
    {
      armUpMotor1.spin(forward, Controller2.Axis2.value()/2, percent);
      armUpMotor2.spin(forward, Controller2.Axis2.value()/2, percent);
    } else {
      if (Controller2.Axis2.value() == 0)
      {
        armUpMotor1.stop();
        armUpMotor2.stop();
      }
    }


    /*---------------------------------------------------------------------------*/
    /*                                Claw control                               */
    /*---------------------------------------------------------------------------*/

    if (Controller2.ButtonL1.pressing() || Controller1.ButtonR1.pressing())
  	{
  		clawBtnPressed = true;
  	}
  	if (((Controller1.ButtonR1.pressing() || Controller1.ButtonL1.pressing()) == false) && clawBtnPressed == true)
  	{
  		clawBtnPressed = false;
  		if (clawOpen == true)
  		{
        clawMotor.spin(reverse, 100, percent);
        wait(0.25, seconds);
        clawMotor.stop();
  			clawOpen = false;
  		}
  		else
  		{
  			clawMotor.spinToPosition(81, degrees);
  			clawOpen = true;
  		}
  	}


    wait(20, msec); // Sleep the task for a short amount of time to
                    // prevent wasted resources.
  }
}

//
// Main will set up the competition functions and callbacks.
//
int main() {
  // Set up callbacks for autonomous and driver control periods.
  Competition.autonomous(autonomous);
  Competition.drivercontrol(usercontrol);

  // Run the pre-autonomous function.
  pre_auton();

  // Prevent main from exiting with an infinite loop.
  while (true) {
    wait(100, msec);
  }
}

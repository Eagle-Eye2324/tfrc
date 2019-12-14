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
// armExtMotor          motor         4               
// armUpMotor1          motor         3               
// armUpMotor2          motor         5               
// clawMotor            motor         9                              
// Controller2          controller                    
// Controller1          controller                    
// ---- END VEXCODE CONFIGURED DEVICES ----

#include "vex.h"
#include <stdio.h>
#include "callbacks.h"

using namespace vex;

// A global instance of competition
competition Competition;

// define your global instances of motors and other devices here

// define your variables here - at least ones that aren't defined in callbacks.cpp

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
      printf("Not connected to a control system");
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
  Brain.Screen.setCursor(1, 1);
  Brain.Screen.print("Brain Battery: %d%%", Brain.Battery.capacity());
  // display the current battery temperature in percent
  Brain.Screen.setCursor(2, 1);
  Brain.Screen.print("Brain Battery Temperature: %d%%", Brain.Battery.temperature(temperatureUnits::celsius));
  
  // Print the battery capacity to the controller screen
  Controller1.Screen.clearScreen();
  Controller1.Screen.setCursor(1, 1);
  Controller1.Screen.print("Brain Battery: %d%%", Brain.Battery.capacity());

  //  print all the stuff to the computer
  printf("Brain Battery Capacity: %lu%%", Brain.Battery.capacity());
  printf("Brain Battery Temperature: %f%%", Brain.Battery.temperature(temperatureUnits::celsius));


  // Begin autonomous
  RFDrive.spin(forward, 100, percent);
  LFDrive.spin(forward, 100, percent);
  RRDrive.spin(forward, 100, percent);
  LRDrive.spin(forward, 100, percent);
  waitUntil(RFDrive.position(degrees) >= 401);
  RFDrive.spin(reverse, 100, percent);
  LFDrive.spin(reverse, 100, percent);
  RRDrive.spin(reverse, 100, percent);
  LRDrive.spin(reverse, 100, percent);
  waitUntil(RFDrive.position(degrees) <= 0);
  RFDrive.stop();
  LFDrive.stop();
  RRDrive.stop();
  LRDrive.stop();
  
  // End autonomous
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
    Controller1.Screen.print("Brain Battery: %d%%", Brain.Battery.capacity());
    printf("Brain Battery Capacity: %lu%%", Brain.Battery.capacity());
    printf("Brain Battery Temperature: %f%%", Brain.Battery.temperature(temperatureUnits::celsius));

    /*=============================User control start============================*/

    // Drive motor control
    RFDrive.spin(directionType::fwd, Controller1.Axis3.position()*driveMultiplier, percentUnits::pct);
    RRDrive.spin(directionType::fwd, Controller1.Axis3.position()*driveMultiplier, percentUnits::pct);
    LFDrive.spin(directionType::fwd, Controller1.Axis2.position()*driveMultiplier, percentUnits::pct);
    LRDrive.spin(directionType::fwd, Controller1.Axis2.position()*driveMultiplier, percentUnits::pct);


    // Arm extenstion control
    Controller1.ButtonL1.pressed(armOut);
    Controller1.ButtonL1.released(stopArmExtenstion);
    Controller1.ButtonL2.pressed(armIn);
    Controller1.ButtonL2.released(stopArmExtenstion);


    // Arm elevation control
    Controller1.ButtonR1.pressed(armUp);
    Controller1.ButtonR1.released(stopArmElevation);
    Controller1.ButtonR2.pressed(armDown);
    Controller1.ButtonR2.released(stopArmElevation);


    // Claw control
    Controller1.ButtonRight.pressed(closeClaw);
    Controller1.ButtonRight.released(stopClaw);
    Controller1.ButtonLeft.pressed(openClaw);
    Controller1.ButtonLeft.released(stopClaw);
    Controller1.ButtonA.pressed(clawControl);
    Controller1.ButtonA.released(stopClaw);

    
    // Drive motor speed control
    // Controller1.ButtonUp.pressed(increaseMultiplier);
    // Controller1.ButtonDown.pressed(decreaseMultiplier);
    // Controller1.Screen.setCursor(2, 1);
    // Controller1.Screen.print("Drive speed: %f%%", driveMultiplier);
    // printf("%f%%", driveMultiplier);

    /*==============================User control end=============================*/

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

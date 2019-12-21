/*----------------------------------------------------------------------------*/
/*                                                                            */
/*    Module:       callbacks.cpp                                             */
/*    Author:       Robbie Munro                                              */
/*    Created:      Fri Sept 29 2019                                          */
/*    Description:  Callback definitions                                      */
/*                                                                            */
/*----------------------------------------------------------------------------*/

#include "vex.h"

// Variable definitions - these variables are need for the callbacks
bool armExtPressed;
bool armUpPressed;
bool clawOpen;
bool clawBtnPressed;
float driveMultiplier = 0.40;

/*---------------------------------------------------------------------------*/
/*                         Drive motor speed control                         */
/*---------------------------------------------------------------------------*/

// Increases the drive motor multiplier in increments of 10 percent
void increaseMultiplier() {
  driveMultiplier += 0.1;
}

// Decreases the drive motor multiplier in increments of 10 percent
void decreaseMultiplier() {
  driveMultiplier -= 0.1;
}


/*---------------------------------------------------------------------------*/
/*                                Claw control                               */
/*---------------------------------------------------------------------------*/

// Opens the claw
void openClaw() {
  clawMotor.spin(forward, 50, percent);
}

// Closes the claw
void closeClaw() {
  clawMotor.spin(reverse, 50, percent);
}

// Stops the claw
void stopClaw() {
  clawMotor.stop();
}

// Single button claw control
void clawControl() {
  if (clawOpen) {
    clawMotor.spin(reverse, 100, percent);
    wait(0.25, seconds);
    clawMotor.stop();
    clawOpen = false;
  } else if (!clawOpen) {
    clawMotor.spinToPosition(180, degrees);
    clawOpen = true;
  }
}


/*---------------------------------------------------------------------------*/
/*                           Arm elevation control                           */
/*---------------------------------------------------------------------------*/

// Raises the arm
void armControl() {
  if (armExtMotor.position(degrees) >= 260)
  {
    if (armUpMotor1.position(degrees) <= 500)
    {
      armUpMotor1.setVelocity(40, percent);
      armUpMotor2.setVelocity(40, percent);
      armUpMotor1.spin(forward);
      armUpMotor2.spin(forward);
    } else {
      armUpMotor1.stop();
      armUpMotor2.stop();
    }
  } else {
    if (armUpMotor1.position(degrees) <= 400)
    {
      armUpMotor1.setVelocity(40, percent);
      armUpMotor2.setVelocity(40, percent);
      armUpMotor1.spin(forward);
      armUpMotor2.spin(forward);
    } else {
      armUpMotor1.stop();
      armUpMotor2.stop();
    }
  }
}

// Lowers the arm
void armDown() {
  armUpMotor1.spin(reverse);
  armUpMotor2.spin(reverse);
}

// Stops the arm
void stopArmElevation() {
  armUpMotor1.stop();
  armUpMotor2.stop();
}



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
float driveMultiplier = 0.4;

/*---------------------------------------------------------------------------*/
/*                         Drive motor speed control                         */
/*---------------------------------------------------------------------------*/

// Increases the drive motor multiplier in increments of 10 percent
void increaseMultiplier() {
  // switch(int(driveMultiplier*10)) {
  //   case 1:
  //     driveMultiplier = 0.2;

  //     break;
  //   case 2:
  //     driveMultiplier = 0.3;
  //     break;
  //   case 3:
  //     driveMultiplier = 0.4;
  //     break;
  //   case 4:
  //     driveMultiplier = 0.5;
  //     break;
  //   case 5:
  //     driveMultiplier = 0.6;
  //     break;
  //   case 6:
  //     driveMultiplier = 0.7;
  //     break;
  //   case 7:
  //     driveMultiplier = 0.8;
  //     break;
  //   case 8:
  //     driveMultiplier = 0.9;
  //     break;
  //   case 9:
  //     driveMultiplier = 1.0;
  //     break;
  // }
  if(driveMultiplier == 1.0) {
    driveMultiplier = 1.0;
  } else {
    driveMultiplier += 0.02;
  }
}

// Decreases the drive motor multiplier in increments of 10 percent
void decreaseMultiplier() {
  // switch(int(driveMultiplier*10)) {
  //   case 2:
  //     driveMultiplier = 0.1;
  //     break;
  //   case 3:
  //     driveMultiplier = 0.2;
  //     break;
  //   case 4:
  //     driveMultiplier = 0.3;
  //     break;
  //   case 5:
  //     driveMultiplier = 0.4;
  //     break;
  //   case 6:
  //     driveMultiplier = 0.5;
  //     break;
  //   case 7:
  //     driveMultiplier = 0.6;
  //     break;
  //   case 8:
  //     driveMultiplier = 0.7;
  //     break;
  //   case 9:
  //     driveMultiplier = 0.8;
  //     break;
  //   case 10:
  //     driveMultiplier = 0.9;
  //     break;
  // }
  if(driveMultiplier == 0.1) {
    driveMultiplier = 0.1;
  } else {
    driveMultiplier -= 0.02;
  }
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
void armUp() {
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
  armUpMotor1.setVelocity(40, percent);
  armUpMotor2.setVelocity(40, percent);
  armUpMotor1.spin(reverse);
  armUpMotor2.spin(reverse);
}

// Stops the arm
void stopArmElevation() {
  armUpMotor1.stop();
  armUpMotor2.stop();
}


/*---------------------------------------------------------------------------*/
/*                           Arm extenstion control                          */
/*---------------------------------------------------------------------------*/

// Extends the arm
void armOut() {
  if (armExtMotor.position(degrees) >= 740)
  {
    armExtMotor.stop();
  } else {
    armExtMotor.spin(forward);
  }
}

// Retracts the arm
void armIn() {
  if (armUpMotor1.position(degrees) >= 400)
  {
    if (armExtMotor.position(degrees) <= 260)
    {
      armExtMotor.stop();
    } else {
      armExtMotor.spin(reverse);
    }
  } else {
    if (armExtMotor.position(degrees) <= 0)
    {
      armExtMotor.stop();
    } else {
      armExtMotor.spin(reverse);
    }
  }
}

void stopArmExtenstion() {
  armExtMotor.stop();
}
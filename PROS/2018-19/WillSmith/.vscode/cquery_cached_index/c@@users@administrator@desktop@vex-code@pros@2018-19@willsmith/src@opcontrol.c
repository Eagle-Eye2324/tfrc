/** @file opcontrol.c
 * @brief File for operator control code
 *
 * This file should contain the user operatorControl() function and any functions related to it.
 *
 * PROS contains FreeRTOS (http://www.freertos.org) whose source code may be
 * obtained from http://sourceforge.net/projects/freertos/files/ or on request.
 */

#include "main.h"

/*
 * Runs the user operator control code. This function will be started in its own task with the
 * default priority and stack size whenever the robot is enabled via the Field Management System
 * or the VEX Competition Switch in the operator control mode. If the robot is disabled or
 * communications is lost, the operator control task will be stopped by the kernel. Re-enabling
 * the robot will restart the task, not resume it from where it left off.
 *
 * If no VEX Competition Switch or Field Management system is plugged in, the VEX Cortex will
 * run the operator control task. Be warned that this will also occur if the VEX Cortex is
 * tethered directly to a computer via the USB A to A cable without any VEX Joystick attached.
 *
 * Code running in this task can take almost any action, as the VEX Joystick is available and
 * the scheduler is operational. However, proper use of delay() or taskDelayUntil() is highly
 * recommended to give other tasks (including system tasks such as updating LCDs) time to run.
 *
 * This task should never exit; it should end with some kind of infinite loop, even if empty.
 */
void operatorControl() {
	int powerRight;
	int powerLeft;
	while (1 == 1) {
		// Right side drive motors
		powerRight = joystickGetAnalog(1, 2); // Get value of vertical axis on right stick
		motorSet(RM_DRIVE_MOTOR, powerRight); // Set right middle motor
		motorSet(RRF_DRIVE_MOTOR, powerRight); // Set right rear front motor
		motorSet(RRR_DRIVE_MOTOR, powerRight); // Set right rear rear motors

		// Left side drive motorSet
		powerLeft = joystickGetAnalog(1, 3); // Get value of vertical axis on left stick
		motorSet(LM_DRIVE_MOTOR, powerLeft); // Set left middle motor
		motorSet(LRF_DRIVE_MOTOR, powerLeft); // Set left rear front motor
		motorSet(LRR_DRIVE_MOTOR, powerLeft); // Set left rear rear motors
	}
}

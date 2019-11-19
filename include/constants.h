//
// Created by ariel on 11/15/19.
//

#ifndef ROBOT_CODE_CONSTANTS_H
#define ROBOT_CODE_CONSTANTS_H

#include "main.h"

#define LEFT_MOTOR_PORT 1
#define RIGHT_MOTOR_PORT -2

#define MOTOR_MOVE_MAX 127

#define TRAY_IN true
#define TRAY_OUT false

#define INTAKE_MOTOR_PORT_LEFT 3 ///TODO: Change to intake motor left to actual value
#define INTAKE_MOTOR_PORT_RIGHT -4 ///TODO: Change intake motor right to actual value
#define INTAKE_BUTTON pros::E_CONTROLLER_DIGITAL_A ///TODO: Change intake button to actual value
#define OUTTAKE_BUTTON pros::E_CONTROLLER_DIGITAL_B

#define INTAKE_POSITION_MOTOR_PORT 5 /// TODO: Change intake position motor to actual port

#define AUTO_DEBUG 0

#endif //ROBOT_CODE_CONSTANTS_H

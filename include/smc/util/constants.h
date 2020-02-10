//
// Created by ariel on 11/15/19.
//
#ifndef ROBOT_CODE_CONSTANTS_H
#define ROBOT_CODE_CONSTANTS_H

#include "main.h"
#include "okapi/api.hpp"

using namespace okapi;
namespace robot {
    /* Begin drive motor block */
    const int FRONT_LEFT_DRIVE_MOTOR_PORT = 18;
    const int FRONT_RIGHT_DRIVE_MOTOR_PORT = -17;
    const int BACK_LEFT_DRIVE_MOTOR_PORT = 13;
    const int BACK_RIGHT_DRIVE_MOTOR_PORT = -12;
    /* End drive motor block */


    /* Begin intake block */
    const int INTAKE_MOTOR_PORT_LEFT = -20; // TODO: Placeholder value
    const int INTAKE_MOTOR_PORT_RIGHT = 11; // TODO: Placeholder value
    const int INTAKE_POS_MOTOR_PORT_LEFT = -10;
    const int INTAKE_POS_MOTOR_PORT_RIGHT = 1;

    const char INTAKE_POS_LIMIT_SWITCH_TOP = 'A'; // TODO: Placeholder value
    const char INTAKE_POS_LIMIT_SWITCH_BOTTOM = 'B'; //TODO: Placeholder value

    const float INTAKE_DOWN_POS = 0;
    const float INTAKE_UP_POS_LEFT = 910.0;
    const float INTAKE_UP_POS_RIGHT = 910.0;
    /* End intake block */


    /* Begin tray block */
    const int TRAY_POS_MOTOR_PORT = 19;
    const int TRAY_MOTOR_POS_UP = 140; // TODO: Placeholder value

    const char TRAY_POS_DOWN_LIMIT_SWITCH = 'H';
    /* End tray block */


    /* Begin random global pointer block */
    extern std::shared_ptr<okapi::ChassisController> chassis;
    extern std::shared_ptr<okapi::AsyncMotionProfileController> profile_controller;
    /* End random global pointer block */
}

namespace bindings {
    // TODO: when all buttons have been mapped, make a comment describing what each one does
    const auto INTAKE_BUTTON  = okapi::ControllerDigital::R1;
    const auto OUTTAKE_BUTTON = okapi::ControllerDigital::L1;

    const auto TOGGLE_INTAKE_POS = okapi::ControllerDigital::B;
    const auto INTAKE_POS_UP = okapi::ControllerDigital::up;
    const auto INTAKE_POS_DOWN = okapi::ControllerDigital::down;

    const auto PLACE_STACK = okapi::ControllerDigital::A;
    const auto LOWER_TRAY = okapi::ControllerDigital::right;
    const auto RAISE_TRAY = okapi::ControllerDigital::left;

    const auto DRIVE_BRAKE_TOGGLE = okapi::ControllerDigital::B;
}

namespace constants {
    const int MOTOR_MOVE_MAX = 127;

    const auto OKAPI_BRAKE = okapi::AbstractMotor::brakeMode::brake;
    const auto OKAPI_COAST = okapi::AbstractMotor::brakeMode::coast;

    const int VELOCITY_AUTONOMOUS = 200;
}


#endif //ROBOT_CODE_CONSTANTS_H
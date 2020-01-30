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
    const int FRONT_LEFT_DRIVE_MOTOR_PORT = 0;
    const int FRONT_RIGHT_DRIVE_MOTOR_PORT = 0;
    const int BACK_LEFT_DRIVE_MOTOR_PORT = 13;
    const int BACK_RIGHT_DRIVE_MOTOR_PORT = 2;
    /* End drive motor block */


    /* Begin intake block */
    const int INTAKE_MOTOR_PORT_LEFT = -11; // TODO: Placeholder value
    const int INTAKE_MOTOR_PORT_RIGHT = 1; // TODO: Placeholder value
    const int INTAKE_POS_MOTOR_PORT_LEFT = -12;
    const int INTAKE_POS_MOTOR_PORT_RIGHT = 3;

    const char INTAKE_POS_LIMIT_SWITCH_UP = 'A'; // TODO: Placeholder value
    const char INTAKE_POS_LIMIT_SWITCH_DOWN = 'A'; //TODO: Placeholder value

    const float INTAKE_DOWN_POS = 0;
    const float INTAKE_UP_POS_LEFT = 910.0;
    const float INTAKE_UP_POS_RIGHT = 910.0;
    /* End intake block */


    /* Begin tray block */
    const int TRAY_POS_MOTOR_PORT = 15;
    const int TRAY_MOTOR_POS_UP = 140; // TODO: Placeholder value

    const char TRAY_POS_DOWN_LIMIT_SWITCH = 'H';
    /* End tray block */


    /* Begin random global pointer block */
    extern std::shared_ptr<okapi::ChassisController> chassis;
    extern std::shared_ptr<okapi::AsyncMotionProfileController> profile_controller;
    /* End random global pointer block */
}

namespace bindings {
    const auto INTAKE_BUTTON  = okapi::ControllerDigital::R1; // TODO: Placeholder value
    const auto OUTTAKE_BUTTON = okapi::ControllerDigital::L1;

    const auto TOGGLE_INTAKE_POS = okapi::ControllerDigital::B;
    const auto INTAKE_POS_UP = okapi::ControllerDigital::up;
    const auto INTAKE_POS_DOWN = okapi::ControllerDigital::left;

    const auto TOGGLE_TRAY_POS = okapi::ControllerDigital::A;
    const auto LOWER_TRAY = okapi::ControllerDigital::down;
    const auto RAISE_TRAY = okapi::ControllerDigital::right;

    const auto DRIVE_BRAKE_TOGGLE = okapi::ControllerDigital::X;
}

namespace constants {
    const int MOTOR_MOVE_MAX = 127;

    const auto OKAPI_BRAKE = okapi::AbstractMotor::brakeMode::brake;
    const auto OKAPI_COAST = okapi::AbstractMotor::brakeMode::coast;
}

#endif //ROBOT_CODE_CONSTANTS_H
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
    const int FRONT_LEFT_DRIVE_MOTOR_PORT = 20;
    const int FRONT_RIGHT_DRIVE_MOTOR_PORT = -11;
    const int BACK_LEFT_DRIVE_MOTOR_PORT = 10;
    const int BACK_RIGHT_DRIVE_MOTOR_PORT = -1;
    /* End drive motor block */


    /* Begin intake block */
    const int INTAKE_MOTOR_PORT_LEFT = -9;
    const int INTAKE_MOTOR_PORT_RIGHT = 2;
    /* End intake block */


    /* Begin tray block */
    const int TRAY_POS_MOTOR_PORT = 19;
    const int TRAY_MOTOR_POS_UP = 750; // TODO: Placeholder value

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

    const auto TRAY_POS_UP = okapi::ControllerDigital::up;
    const auto TRAY_POS_DOWN = okapi::ControllerDigital::down;

    const auto PLACE_STACK = okapi::ControllerDigital::A;
    const auto LOWER_TRAY = okapi::ControllerDigital::right;
    const auto RAISE_TRAY = okapi::ControllerDigital::left;

    const auto DRIVE_BRAKE_TOGGLE = okapi::ControllerDigital::B;
}

namespace constants {
    const int MOTOR_MOVE_MAX = 127;

    const int AUTO_TRAY_SPEED = 50;

    const auto OKAPI_BRAKE = okapi::AbstractMotor::brakeMode::brake;
    const auto OKAPI_COAST = okapi::AbstractMotor::brakeMode::coast;

    const int VELOCITY_AUTONOMOUS = 200;
}


#endif //ROBOT_CODE_CONSTANTS_H
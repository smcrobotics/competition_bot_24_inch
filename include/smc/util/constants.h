//
// Created by ariel on 11/15/19.
//
#ifndef ROBOT_CODE_CONSTANTS_H
#define ROBOT_CODE_CONSTANTS_H

#include "main.h"
#include "okapi/api.hpp"

using namespace okapi;
namespace robot {
    const int FRONT_LEFT_DRIVE_MOTOR_PORT = 16;
    const int FRONT_RIGHT_DRIVE_MOTOR_PORT = -15;
    const int BACK_LEFT_DRIVE_MOTOR_PORT = 12;
    const int BACK_RIGHT_DRIVE_MOTOR_PORT = -11;

    const int INTAKE_MOTOR_PORT_LEFT = -1; /// TODO: Change to intake motor left to actual value
    const int INTAKE_MOTOR_PORT_RIGHT = 10; /// TODO: Change intake motor right to actual value
    const int INTAKE_POS_MOTOR_PORT_LEFT = -9;
    const int INTAKE_POS_MOTOR_PORT_RIGHT = 2;

    const int TRAY_POS_MOTOR_PORT = 7;

    const float INTAKE_DOWN_POS = 0;
    const float INTAKE_UP_POS_LEFT = 410.0;
    const float INTAKE_UP_POS_RIGHT = 410.0;

    extern std::shared_ptr<okapi::ChassisControllerIntegrated> chassis;
    extern std::shared_ptr<okapi::AsyncMotionProfileController> profile_controller;
}

namespace bindings {
    const auto INTAKE_BUTTON  = okapi::ControllerDigital::R1; ///TODO: Change intake button to actual value
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
//
// Created by ariel on 11/15/19.
//
#ifndef ROBOT_CODE_CONSTANTS_H
#define ROBOT_CODE_CONSTANTS_H

#include "main.h"
#include "okapi/api.hpp"

#define DEBUG_MODE 0

using namespace okapi;
namespace robot {
    const bool TRAY_IN = true;
    const bool TRAY_OUT = false;

    const int LEFT_MOTOR_PORT = 1;
    const int RIGHT_MOTOR_PORT = -2;

    const int INTAKE_MOTOR_PORT_LEFT = 3; /// TODO: Change to intake motor left to actual value
    const int INTAKE_MOTOR_PORT_RIGHT = -4; /// TODO: Change intake motor right to actual value
    const int INTAKE_FLIP_PORT = 5;

    const int INTAKE_POSITION_MOTOR_PORT = 5; /// TODO: Change intake position motor to actual port

    extern std::shared_ptr<okapi::ChassisControllerIntegrated> chassis;
    extern std::shared_ptr<okapi::AsyncMotionProfileController> profile_controller;
}

namespace bindings {
    const auto INTAKE_BUTTON  = pros::E_CONTROLLER_DIGITAL_A; ///TODO: Change intake button to actual value
    const auto OUTTAKE_BUTTON = pros::E_CONTROLLER_DIGITAL_B;
}

namespace constants {
    const int MOTOR_MOVE_MAX = 127;
}

#endif //ROBOT_CODE_CONSTANTS_H
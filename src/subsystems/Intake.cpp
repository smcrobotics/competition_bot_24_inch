//
// Created by ariel on 11/19/19.
//
#include <iostream>

#include "smc/util/util.h"
#include "smc/subsystems/Intake.h"
#include "smc/util/constants.h"

using std::cout;
using std::endl;

namespace subsystems {
    Intake::Intake() {
        left_intake_motor = util::initMotor(robot::INTAKE_MOTOR_PORT_LEFT, okapi::AbstractMotor::gearset::blue);
        right_intake_motor = util::initMotor(robot::INTAKE_MOTOR_PORT_RIGHT, okapi::AbstractMotor::gearset::blue);
        current_intake_percent = 0;
        current_intake_voltage = 0;
    }

    Intake & Intake::getInstance() {
        static Intake intake;
        return intake;
    }

    void Intake::update() {
        left_intake_motor->moveVelocity(current_intake_voltage);
        right_intake_motor->moveVelocity(current_intake_voltage);
    }

    void Intake::setIntakeVelocity(int percent) {
        current_intake_voltage = ((float) percent / 100.0f) * 12000;
        current_intake_percent = percent;
    }

    void Intake::printDebug() {
        cout << "[DEBUG][Intake] Intake velocity: " << current_intake_percent << endl;
        cout << "[DEBUG][Intake] Intake voltage: " << current_intake_voltage << endl;
    }
}
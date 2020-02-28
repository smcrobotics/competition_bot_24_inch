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
    Intake::Intake() : current_intake_percent(0), current_intake_voltage(0) {
        left_intake_motor = util::initMotor(robot::INTAKE_MOTOR_PORT_LEFT, okapi::AbstractMotor::gearset::blue);
        right_intake_motor = util::initMotor(robot::INTAKE_MOTOR_PORT_RIGHT, okapi::AbstractMotor::gearset::blue);
    }

    Intake * Intake::getInstance() {
        static Intake intake;
        return &intake;
    }

    void Intake::update() {
        left_intake_motor->moveVelocity(current_intake_voltage);
        right_intake_motor->moveVelocity(current_intake_voltage);
    }

    void Intake::printDebug() {
        cout << "[DEBUG][Intake] Intake velocity: " << current_intake_percent << endl;
        cout << "[DEBUG][Intake] Intake voltage: " << current_intake_voltage << endl;
    }

    void Intake::printLCD(int line) {
        std::ostringstream out;
        out << "Intake %: " << current_intake_percent;

        pros::lcd::clear_line(line);
        pros::lcd::set_text(line, out.str());
    }

    void Intake::setIntakeVelocity(int percent) {
        current_intake_voltage = ((float) percent / 100.0f) * 12000;
        current_intake_percent = percent;
    }
}
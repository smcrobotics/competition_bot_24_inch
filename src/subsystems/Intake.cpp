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
    Intake::Intake() : current_percent(0), current_voltage(0) {
        left_motor = util::initMotor(robot::INTAKE_MOTOR_PORT_LEFT);
        right_motor = util::initMotor(robot::INTAKE_MOTOR_PORT_RIGHT);
        pos_motor = util::initMotor(robot::INTAKE_POS_PORT);

        intakeState = Intake::CLOSED;
    }

    Intake * Intake::getInstance() {
        static Intake intake;
        return &intake;
    }

    void Intake::update() {
        left_motor->moveVelocity(current_voltage);
        right_motor->moveVelocity(current_voltage);
    }

    void Intake::printDebug() {
        cout << "[DEBUG][Intake] Intake velocity: " << current_percent << endl;
        cout << "[DEBUG][Intake] Intake voltage: " << current_voltage << endl;
        cout << "[DEBUG][Intake] Intake state: " << ((bool) intakeState ? "Open" : "Closed") << endl;
    }

    void Intake::printLCD(int line) {
        std::ostringstream out;
        out << "[I] Current %: " << current_percent;
        out << ", state: " << (bool) intakeState;

        pros::lcd::clear_line(line);
        pros::lcd::set_text(line, out.str());
    }

    // TODO: make a voltage max constant
    void Intake::setIntakeVelocity(int percent) {
        current_voltage = ((float) percent / 100.0f) * 12000;
        current_percent = percent;
    }

    void Intake::setIntakeState(IntakeState targetState) {
        if (targetState == IntakeState::OPEN)
            // TODO: tune encoder positions
            // TODO: tune move speed
            pos_motor->moveAbsolute(robot::INTAKE_POS_OPEN, constants::INTAKE_MOVE_SPEED);
        else
            pos_motor->moveAbsolute(robot::INTAKE_POS_CLOSED, constants::INTAKE_MOVE_SPEED);

        intakeState = targetState;
    }

    void Intake::toggleIntake() {
        auto intake = getInstance();
        intake->setIntakeState((IntakeState) !((bool) intake->intakeState));
    }
}

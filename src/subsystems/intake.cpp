//
// Created by ariel on 11/19/19.
//
#include "smc/util/util.h"
#include "smc/subsystems/intake.h"
#include "smc/util/constants.h"


namespace intake {
    std::unique_ptr<pros::Motor> left_intake_motor;
    std::unique_ptr<pros::Motor> right_intake_motor;

    void init() {
        left_intake_motor = util::initMotor(robot::INTAKE_MOTOR_PORT_LEFT);
        right_intake_motor = util::initMotor(robot::INTAKE_MOTOR_PORT_RIGHT);
    }

    void moveArmsToPosition(intake::Position position) {
        // TODO: Implement this method
    }
}
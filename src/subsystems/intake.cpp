//
// Created by ariel on 11/19/19.
//
#include "smc/util/util.h"
#include "smc/subsystems/intake.h"
#include "smc/util/constants.h"


namespace intake {
    std::unique_ptr<okapi::Motor> left_intake_motor;
    std::unique_ptr<okapi::Motor> right_intake_motor;
    std::unique_ptr<okapi::Motor> right_intake_pos_motor;
    std::unique_ptr<okapi::Motor> left_intake_pos_motor;

    void init() {
        left_intake_motor = util::initMotor(robot::INTAKE_MOTOR_PORT_LEFT, okapi::AbstractMotor::gearset::blue);
        right_intake_motor = util::initMotor(robot::INTAKE_MOTOR_PORT_RIGHT, okapi::AbstractMotor::gearset::blue);
        left_intake_pos_motor = util::initMotor(robot::INTAKE_POS_MOTOR_PORT_LEFT, okapi::AbstractMotor::gearset::blue);
        right_intake_pos_motor = util::initMotor(robot::INTAKE_POS_MOTOR_PORT_RIGHT, okapi::AbstractMotor::gearset::blue);


        left_intake_pos_motor->tarePosition();
        right_intake_pos_motor->tarePosition();
    }

    void update() {

    }

    void moveArmsToPosition(intake::IntakePosition position) {
        if (position == UP) {
            right_intake_pos_motor->moveAbsolute(robot::INTAKE_UP_POS_RIGHT, 120);
            left_intake_pos_motor->moveAbsolute(robot::INTAKE_UP_POS_LEFT, 120);
        } else if (position == DOWN) {
            right_intake_pos_motor->moveAbsolute(robot::INTAKE_DOWN_POS, 80);
            left_intake_pos_motor->moveAbsolute(robot::INTAKE_DOWN_POS, 80);
        }
    }

    void printPos() {
        std::cout << "Left intake_pos motor position: " << left_intake_pos_motor->getPosition() << std::endl;
        std::cout << "Right intake_pos motor position: " << right_intake_pos_motor->getPosition() << std::endl;
    }

    void setIntakeVelocity(int percent) {
        float voltage = (percent / 100.0f) * 12000;
        left_intake_motor->moveVoltage((int) voltage);
        right_intake_motor->moveVoltage((int) voltage);
    }
}
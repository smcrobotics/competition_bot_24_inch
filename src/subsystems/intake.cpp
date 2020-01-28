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
        left_intake_motor = util::initMotor(robot::INTAKE_MOTOR_PORT_LEFT);
        right_intake_motor = util::initMotor(robot::INTAKE_MOTOR_PORT_RIGHT);
        left_intake_pos_motor = util::initMotor(robot::INTAKE_POS_MOTOR_PORT_LEFT);
        right_intake_pos_motor = util::initMotor(robot::INTAKE_POS_MOTOR_PORT_RIGHT);


        left_intake_pos_motor->tarePosition();
        right_intake_pos_motor->tarePosition();
//        left_intake_pos_motor->move(127);
//        right_intake_pos_motor->move(127);
    }

    void moveArmsToPosition(intake::Position position) {
        if (position == UP) {
            right_intake_pos_motor->moveAbsolute(robot::INTAKE_UP_POS_RIGHT, 120);
            left_intake_pos_motor->moveAbsolute(robot::INTAKE_UP_POS_LEFT, 120);
        } else if (position == DOWN) {
            right_intake_pos_motor->moveAbsolute(robot::INTAKE_DOWN_POS, 80);
            left_intake_pos_motor->moveAbsolute(robot::INTAKE_DOWN_POS, 80);
        }


//        if (position == UP) {
//            left_intake_pos_motor->move(25);
//            right_intake_pos_motor->move(25);
//        } else if (position == DOWN) {
//            left_intake_pos_motor->move(0);
//            right_intake_pos_motor->move(0);
//        }
    }

    void printPos() {
//        std::cout << "left: " << left_intake_pos_motor->getPosition() << std::endl;
//        std::cout << "right: " << right_intake_pos_motor->getPosition() << std::endl;
    }

    void setIntakeVelocity(int percent) {
        float voltage = (percent / 100.0f) * 127;
        left_intake_motor->move((int) voltage);
        right_intake_motor->move((int) voltage);
    }
}
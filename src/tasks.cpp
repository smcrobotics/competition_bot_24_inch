//
// Created by ariel on 11/15/19.
//

#include "api.h"
#include "okapi/api.hpp"

#include "smc/util/constants.h"

void intake_task_fn(void* timeout_ptr) {
    int * timeoutPtr = static_cast<int*>(timeout_ptr);
    auto motor1 = pros::Motor(robot::INTAKE_MOTOR_PORT_LEFT);
    auto motor2 = pros::Motor(robot::INTAKE_MOTOR_PORT_RIGHT);

    motor1.move(constants::MOTOR_MOVE_MAX);
    motor2.move(constants::MOTOR_MOVE_MAX);

    pros::delay(*timeoutPtr);

    motor1.move(0);
    motor2.move(0);
}

const double liftkP = 1.0; // TODO: Replace these values with actual tuned PID loop values
const double liftkI = 0.001;
const double liftkD = 0.02;


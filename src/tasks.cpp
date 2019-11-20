//
// Created by ariel on 11/15/19.
//

#include "api.h"
#include "okapi/api.hpp"

#include "constants.h"

void intake_task_fn(void* timeout_ptr) {
    int * timeoutPtr = static_cast<int*>(timeout_ptr);
    auto motor1 = pros::Motor(INTAKE_MOTOR_PORT_LEFT);
    auto motor2 = pros::Motor(INTAKE_MOTOR_PORT_RIGHT);

    motor1.move(MOTOR_MOVE_MAX);
    motor2.move(MOTOR_MOVE_MAX);

    pros::delay(*timeoutPtr);

    motor1.move(0);
    motor2.move(0);
}

const double liftkP = 1.0; /// TODO: Replace these values with actual tuned PID loop values
const double liftkI = 0.001;
const double liftkD = 0.02;

/// TODO: Consider just moving this into auto code? Having it here seems really dumb
void move_intake_task_fn(void * thisTaskPtr) {
    auto * thisTask = (pros::Task *) thisTaskPtr;
    auto intakePosController = okapi::AsyncControllerFactory::posPID(INTAKE_POSITION_MOTOR_PORT, liftkP, liftkI, liftkD);
    int targetLoc = -600; /// TODO: Change this to the actual target location of intakeDown

    /// Assume that each task notification is a request to toggle up/down
    while (thisTask->notify_take(true, TIMEOUT_MAX)) {
        targetLoc = -targetLoc;
        intakePosController.setTarget(targetLoc);
    }
}
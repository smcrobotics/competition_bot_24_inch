//
// Created by ariel on 11/15/19.
//

#include <>

#ifndef ROBOT_CODE_TASKS_H
#define ROBOT_CODE_TASKS_H

void intake_task_fn(void* p) {
    intakeVel = master.get_digital(INTAKE_TOGGLE_BUTTON) * MOTOR_MOVE_MAX;

    intake_1.move(intakeVel);
    intake_2.move(intakeVel);
}

#endif //ROBOT_CODE_TASKS_H

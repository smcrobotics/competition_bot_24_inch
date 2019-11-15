//
// Created by ariel on 11/15/19.
//

#include <>

#ifndef ROBOT_CODE_TASKS_H
#define ROBOT_CODE_TASKS_H

void intake_task_fn(void* p) {
    mutex_take(mutex, timeout);
    //have timer for duration
    //dont allow other processes to do stuff until this is done
    //
}

#endif //ROBOT_CODE_TASKS_H

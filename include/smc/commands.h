//
// Created by ariel on 11/15/19.
//

#ifndef ROBOT_CODE_TASKS_H
#define ROBOT_CODE_TASKS_H

#include "api.h"
#include "okapi/api.hpp"

#include "smc/util/constants.h"
#include "smc/subsystems/Tray.h"
#include "smc/subsystems/Intake.h"

namespace commands {
    void deployTray();
    void handleTaskThing();


}

#endif //ROBOT_CODE_TASKS_H

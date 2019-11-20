//
// Created by ariel on 11/19/19.
//

#ifndef ROBOT_CODE_UTIL_H
#define ROBOT_CODE_UTIL_H

#include <api.h>
#include <memory>

namespace util {
    // helper function to create motor and set brake mode
    std::unique_ptr<pros::Motor> initMotor(int port);
}

#endif //ROBOT_CODE_UTIL_H

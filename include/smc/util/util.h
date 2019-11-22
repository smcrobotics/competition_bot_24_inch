//
// Created by ariel on 11/19/19.
//

#ifndef ROBOT_CODE_UTIL_H
#define ROBOT_CODE_UTIL_H

#include <api.h>
#include <memory>

namespace util {
    std::unique_ptr<pros::Motor> initMotor(int port);
}

#endif //ROBOT_CODE_UTIL_H

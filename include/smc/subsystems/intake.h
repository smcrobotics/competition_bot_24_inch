//
// Created by ariel on 11/19/19.
//

#ifndef ROBOT_CODE_INTAKE_H
#define ROBOT_CODE_INTAKE_H

#include "api.h"

namespace intake {
    void init();

    void moveArmsToPosition();

    enum Position { UP, DOWN };
}

#endif //ROBOT_CODE_INTAKE_H

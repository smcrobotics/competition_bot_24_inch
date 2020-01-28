//
// Created by ariel on 11/19/19.
//

#ifndef ROBOT_CODE_INTAKE_H
#define ROBOT_CODE_INTAKE_H

#include "api.h"

namespace intake {
    enum Position { UP, DOWN };

    void init();
    void printPos();

    void moveArmsToPosition(Position position);

    void setIntakeVelocity(int percent);

    const int intakePosKP = 1; // TODO: Tune this PID loop
    const int intakePosKI = 1;
    const int intakePosKD = 1;
}

#endif //ROBOT_CODE_INTAKE_H

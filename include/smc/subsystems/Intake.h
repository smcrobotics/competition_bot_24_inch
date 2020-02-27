//
// Created by ariel on 11/19/19.
//

#ifndef ROBOT_CODE_INTAKE_H
#define ROBOT_CODE_INTAKE_H

#include "api.h"
#include "okapi/api.hpp"

namespace intake {
    enum IntakePosition { UP, DOWN };

    void init();

    void update();
    void printPos();

    void moveArmsToPosition(IntakePosition position);

    void setIntakeVelocity(int percent);

    const int intakePosKP = 1; // TODO: Tune this PID loop
    const int intakePosKI = 1;
    const int intakePosKD = 1;

    extern std::unique_ptr<okapi::Motor> left_intake_motor;
    extern std::unique_ptr<okapi::Motor> right_intake_motor;
    extern std::unique_ptr<okapi::Motor> right_intake_pos_motor;
    extern std::unique_ptr<okapi::Motor> left_intake_pos_motor;
}

namespace subsystems {
    class Intake {
    public:
        Intake();
        void update();
        void printDebug();
        void setIntakeVelocity(int percent);

        void intakeMax(); // These methods are for controller bindings, should never be used in code
        void intakeMin();
        void intakeZero();

    private:
        int current_intake_percent;

        std::unique_ptr<okapi::Motor> left_intake_motor;
        std::unique_ptr<okapi::Motor> right_intake_motor;
    };
}

#endif //ROBOT_CODE_INTAKE_H

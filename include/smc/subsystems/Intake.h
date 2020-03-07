//
// Created by ariel on 11/19/19.
//

#ifndef ROBOT_CODE_INTAKE_H
#define ROBOT_CODE_INTAKE_H

#include "api.h"
#include "smc/subsystems/AbstractSubsystem.h"
#include "okapi/api.hpp"

namespace subsystems {
class Intake : public AbstractSubsystem {
    public:
        enum IntakeState { OPEN = 1, CLOSED = 0 };

        static Intake * getInstance();
        Intake(const Intake &) = delete;
        void operator=(const Intake & lhs) = delete;

        void update() override;
        void printDebug() override;
        void printLCD(int line) override;

        void setIntakeVelocity(int percent);

        void setIntakeState(IntakeState pos);
        static void toggleIntake();
        void intakeMoveManual(int motorSpeedPercent);

    private:
        Intake();

        IntakeState intakeState;

        float current_voltage;
        int current_percent;
        std::unique_ptr<okapi::Motor> left_motor;
        std::unique_ptr<okapi::Motor> right_motor;

        std::unique_ptr<okapi::Motor> pos_motor;
    };
}

#endif //ROBOT_CODE_INTAKE_H

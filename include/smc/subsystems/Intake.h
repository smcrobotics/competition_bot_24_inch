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
        static Intake * getInstance();
        Intake(const Intake &) = delete;
        void operator=(const Intake & lhs) = delete;

        void update() override;
        void printDebug() override;
        void printLCD(int line) override;
        void setIntakeVelocity(int percent);

    private:
        Intake();

        float current_intake_voltage;
        int current_intake_percent;
        std::unique_ptr<okapi::Motor> left_intake_motor;
        std::unique_ptr<okapi::Motor> right_intake_motor;
    };
}

#endif //ROBOT_CODE_INTAKE_H

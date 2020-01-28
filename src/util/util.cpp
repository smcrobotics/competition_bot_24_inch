#include "smc/robot.h"
#include "smc/util/util.h"
#include "okapi/api.hpp"

namespace util {
    // helper function to create motor and set brake mode
    std::unique_ptr<okapi::Motor> initMotor(int port) {
        // E_MOTOR_GEARSET_18 is for 200rpm motors, default for v5 smart motor
        std::unique_ptr<okapi::Motor> motor = std::make_unique<okapi::Motor>(port);
        motor->setBrakeMode(constants::OKAPI_BRAKE);
        motor->setGearing(okapi::AbstractMotor::gearset::green);
        return motor;
    }
}


#include "smc/robot.h"
#include "smc/util/util.h"
#include "okapi/api.hpp"

using std::unique_ptr;
using std::make_unique;

namespace util {
    // helper function to create motor and set brake mode
    unique_ptr<okapi::Motor> initMotor(int port, okapi::AbstractMotor::gearset gearset) {
        // E_MOTOR_GEARSET_18 is for 200rpm motors, default for v5 smart motor
        unique_ptr<okapi::Motor> motor = make_unique<okapi::Motor>(port);
        motor->setBrakeMode(constants::OKAPI_BRAKE);
        motor->setGearing(gearset);
        return motor;
    }

    unique_ptr<okapi::Motor> initMotor(int port) {
        return initMotor(port, okapi::Motor::gearset::green);
    }

    unique_ptr<okapi::ADIButton> initLimitSwitch(char port) {
        return make_unique<okapi::ADIButton>(port, false);
    }

}


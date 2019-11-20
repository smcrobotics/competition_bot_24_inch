#include "smc/util/util.h"


namespace util {
    // helper function to create motor and set brake mode
    std::unique_ptr<pros::Motor> initMotor(int port) {
        // E_MOTOR_GEARSET_18 is for 200rpm motors, default for v5 smart motor
        std::unique_ptr<pros::Motor> motor = std::make_unique<pros::Motor>(port, pros::E_MOTOR_GEARSET_18);
        motor->set_brake_mode(pros::E_MOTOR_BRAKE_BRAKE);
        return motor;
    }
}

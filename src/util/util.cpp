#include "smc/util/util.h"

<<<<<<< HEAD
namespace util {
=======

namespace util {
    // helper function to create motor and set brake mode
>>>>>>> 05e8e3893628bb980f39dfd5da696b9b2ff0d15d
    std::unique_ptr<pros::Motor> initMotor(int port) {
        // E_MOTOR_GEARSET_18 is for 200rpm motors, default for v5 smart motor
        std::unique_ptr<pros::Motor> motor = std::make_unique<pros::Motor>(port, pros::E_MOTOR_GEARSET_18);
        motor->set_brake_mode(pros::E_MOTOR_BRAKE_BRAKE);
        return motor;
    }
<<<<<<< HEAD
}
=======
}
>>>>>>> 05e8e3893628bb980f39dfd5da696b9b2ff0d15d

#include "main.h"

#include "smc/subsystems/drive.h"
#include "smc/util/util.h"
#include "smc/util/constants.h"

using namespace okapi;

namespace drive {
    std::unique_ptr<pros::Motor> back_left_wheels;
    std::unique_ptr<pros::Motor> back_right_wheels;

    void init() {
        drive::back_left_wheels = util::initMotor(robot::LEFT_MOTOR_PORT);
        drive::back_right_wheels = util::initMotor(robot::RIGHT_MOTOR_PORT);
    }

    void opControl(double left, double right) {
        drive::back_left_wheels->move(left);
        drive::back_right_wheels->move(right);
    }
}
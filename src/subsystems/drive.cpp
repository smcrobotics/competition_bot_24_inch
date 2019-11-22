#include "main.h"

#include "smc/subsystems/drive.h"

using namespace okapi;

namespace drive {
    std::unique_ptr<pros::Motor> back_left_wheels;
    std::unique_ptr<pros::Motor> back_right_wheels;

    void init() {
        drive::back_left_wheels = util::initMotor(robot::BACK_LEFT_WHEELS_PORT);
        drive::back_right_wheels = util::initMotor(BACK_RIGHT_WHEELS_PORT);
    }

    void opControl(double left, double right) {
        drive::back_left_wheels->move(left_y);
        drive::back_right_wheels->move(right_y);
    }
}
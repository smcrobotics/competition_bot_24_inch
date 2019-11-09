#include "main.h"

// using namespace okapi;

namespace drive {
    void init() {
        back_left_wheels = std::make_unique<Motor>(BACK_LEFT_WHEELS_PORT);
        back_right_wheels = std::make_unique<Motor>(BACK_RIGHT_WHEELS_PORT, true); // bool flag (e.g. true) inverts motor
        front_left_wheels = std::make_unique<Motor>(FRONT_LEFT_WHEELS_PORT);
        front_right_wheels = std::make_unique<Motor>(FRONT_RIGHT_WHEELS_PORT, true);
    }

    void opControl(double right_x, double right_y, double left_x) {
        front_left_wheels.move(right_y + right_x + left_x);
        back_left_wheels.move(right_y - right_x + left_x);
        front_right_wheels.move(-right_y + right_x + left_x);
        back_right_wheels.move(-right_y - right_x + left_x);
    }

    std::unique_ptr<pros::Motor> back_left_wheels;
    std::unique_ptr<pros::Motor> back_right_wheels;
    std::unique_ptr<pros::Motor> front_left_wheels;
    std::unique_ptr<pros::Motor> front_right_wheels;
}
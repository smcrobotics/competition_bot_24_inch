#include "main.h"

using namespace okapi;

namespace drive {
    std::unique_ptr<pros::Motor> back_left_wheels;
    std::unique_ptr<pros::Motor> back_right_wheels;
    std::unique_ptr<pros::Motor> front_left_wheels;
    std::unique_ptr<pros::Motor> front_right_wheels;

    void init() {
        drive::back_left_wheels = std::make_unique<pros::Motor>(BACK_LEFT_WHEELS_PORT);
        // bool flag (e.g. true) inverts motor
        drive::back_right_wheels = std::make_unique<pros::Motor>(BACK_RIGHT_WHEELS_PORT, true);
        drive::front_left_wheels = std::make_unique<pros::Motor>(FRONT_LEFT_WHEELS_PORT);
        drive::front_right_wheels = std::make_unique<pros::Motor>(FRONT_RIGHT_WHEELS_PORT, true);
    }

    void opControl(double right_x, double right_y, double left_x) {
        drive::front_left_wheels->move(right_y + right_x + left_x);
        drive::back_left_wheels->move(right_y - right_x + left_x);
        drive::front_right_wheels->move(-right_y + right_x + left_x);
        drive::back_right_wheels->move(-right_y - right_x + left_x);
    }
}
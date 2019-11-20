#include "main.h"

#include "smc/subsystems/drive.h"

using namespace okapi;

namespace drive {
    std::unique_ptr<pros::Motor> back_left_wheels;
    std::unique_ptr<pros::Motor> back_right_wheels;
    std::unique_ptr<pros::Motor> front_left_wheels;
    std::unique_ptr<pros::Motor> front_right_wheels;

    // helper function to create motor and set brake mode

    void init() {
        drive::back_left_wheels = drive::initMotor(BACK_LEFT_WHEELS_PORT);
        drive::back_right_wheels = drive::initMotor(BACK_RIGHT_WHEELS_PORT);
        drive::front_left_wheels = drive::initMotor(FRONT_LEFT_WHEELS_PORT);
        drive::front_right_wheels = drive::initMotor(FRONT_RIGHT_WHEELS_PORT);
    }

    void opControl(double right_x, double right_y, double left_x) {
        // see https://www.youtube.com/watch?v=1-Ju_VqYLAU&t=44s for intuition
        // on why this control scheme works for an xDrive chassis
        drive::front_left_wheels->move(right_y + right_x + left_x);
        drive::back_left_wheels->move(right_y - right_x + left_x);
        drive::front_right_wheels->move(-right_y + right_x + left_x);
        drive::back_right_wheels->move(-right_y - right_x + left_x);
    }
}
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

    void opControl(pros::Controller & master) {
        int rightX = master.get_analog(pros::E_CONTROLLER_ANALOG_RIGHT_X) / 127.0;
        int rightY = master.get_analog(pros::E_CONTROLLER_ANALOG_RIGHT_Y) / 127.0;
        int leftX = master.get_analog(pros::E_CONTROLLER_ANALOG_LEFT_X) / 127.0;
        int leftY = master.get_analog(pros::E_CONTROLLER_ANALOG_LEFT_Y) / 127.0;

        if (rightX != 0 || rightY != 0)
            robot::chassis->arcade(rightY, rightX);
        else {
            robot::chassis->forward(leftY); /// TODO: Make this less sensitive (i.e. slower) than right stick analog
            robot::chassis->right(leftX);
        }
    }
}
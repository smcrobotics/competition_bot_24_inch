#include "main.h"

#include "smc/subsystems/drive.h"
#include "smc/util/util.h"
#include "smc/util/constants.h"

#include <math.h>

using namespace okapi;

namespace drive {
    std::unique_ptr<pros::Motor> back_left_wheels;
    std::unique_ptr<pros::Motor> back_right_wheels;

    void init() {
        drive::back_left_wheels = util::initMotor(robot::LEFT_MOTOR_PORT);
        drive::back_right_wheels = util::initMotor(robot::RIGHT_MOTOR_PORT);
    }

    void opControl(pros::Controller & master) {
        double leftAnalogY = master.get_analog(pros::E_CONTROLLER_ANALOG_LEFT_Y) / 127.0;
        double leftAnalogX = master.get_analog(pros::E_CONTROLLER_ANALOG_LEFT_X) / 127.0;
        double rightAnalogY = master.get_analog(pros::E_CONTROLLER_ANALOG_RIGHT_Y) / 127.0;
        double rightAnalogX = master.get_analog(pros::E_CONTROLLER_ANALOG_RIGHT_X) / 127.0;

        double rightY = pow(abs(rightAnalogY), 1.5) * rightAnalogY / abs(rightAnalogY);
        double rightX = pow(abs(rightAnalogX), 1.5) * rightAnalogX / abs(rightAnalogX);
        double leftX = pow(abs(leftAnalogX), 1.5) * leftAnalogX / abs(leftAnalogX);
        double leftY = pow(abs(leftAnalogY), 1.5) * leftAnalogY / abs(leftAnalogY);

        robot::chassis->tank(leftY, rightY);
    }
}
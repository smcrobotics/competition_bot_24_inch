#include "main.h"

using namespace okapi;

namespace drive {
    std::unique_ptr<pros::Motor> back_left_wheels;
    std::unique_ptr<pros::Motor> back_right_wheels;
    std::unique_ptr<pros::Motor> front_left_wheels;
    std::unique_ptr<pros::Motor> front_right_wheels;

    // helper function to create motor and set brake mode
    std::unique_ptr<pros::Motor> initDriveMotor(int port) {
        // E_MOTOR_GEARSET_18 is for 200rpm motors, default for v5 smart motor
        std::unique_ptr<pros::Motor> motor = std::make_unique<pros::Motor>(port, pros::E_MOTOR_GEARSET_18);
        motor->set_brake_mode(pros::E_MOTOR_BRAKE_BRAKE);
        return motor;
    }

    void init() {
        drive::back_left_wheels = drive::initDriveMotor(BACK_LEFT_WHEELS_PORT);
        drive::back_right_wheels = drive::initDriveMotor(BACK_RIGHT_WHEELS_PORT);
        drive::front_left_wheels = drive::initDriveMotor(FRONT_LEFT_WHEELS_PORT);
        drive::front_right_wheels = drive::initDriveMotor(FRONT_RIGHT_WHEELS_PORT);
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
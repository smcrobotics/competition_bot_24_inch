//
// Created by ariel on 11/19/19.
//
#include "subsystems/intake.h"
#include "constants.h"


namespace intake {
    pros::Motor left_intake_motor;
    pros::Motor right_intake_motor;

    // helper function to create motor and set brake mode
    pros::Motor initIntakeMotor(int port) {
        // E_MOTOR_GEARSET_18 is for 200rpm motors, default for v5 smart motor
        pros::Motor motor(port, pros::E_MOTOR_GEARSET_18);
        motor.set_brake_mode(pros::E_MOTOR_BRAKE_BRAKE);
        return motor;
    }

    void init() {
        left_intake_motor = initIntakeMotor(robot::INTAKE_MOTOR_PORT_LEFT);
        right_intake_motor = initDriveMotor(robot::INTAKE_MOTOR_PORT_RIGHT);
    }

    void moveToPosition(enum position) {
        intake::left_intake_motor.move();
        intake::back_left_wheels->move(right_y - right_x + left_x);
        intake::front_right_wheels->move(-right_y + right_x + left_x);
        intake::back_right_wheels->move(-right_y - right_x + left_x);
    }
}
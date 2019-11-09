#include "main.h"
using namespace okapi;
using std::cout;
using std::endl;
/**
 * A callback function for LLEMU's center button.
 *
 * When this callback is fired, it will toggle line 2 of the LCD text between
 * "I was pressed!" and nothing.
 */
void on_center_button() {
    static bool pressed = false;
    pressed = !pressed;
    if (pressed) {
        pros::lcd::set_text(2, "I was pressed!");
    } else {
        pros::lcd::clear_line(2);
    }
}

/**
 * Runs initialization code. This occurs as soon as the program is started.
 *
 * All other competition modes are blocked by initialize; it is recommended
 * to keep execution time for this mode under a few seconds.
 */
void initialize() {
    pros::lcd::initialize();
    pros::lcd::set_text(1, "Hello PROS User!");

    pros::lcd::register_btn1_cb(on_center_button);

}

/**
 * Runs while the robot is in the disabled state of Field Management System or
 * the VEX Competition Switch, following either autonomous or opcontrol. When
 * the robot is enabled, this task will exit.
 */
void disabled() {}

/**
 * Runs after initialize(), and before autonomous when connected to the Field
 * Management System or the VEX Competition Switch. This is intended for
 * competition-specific initialization routines, such as an autonomous selector
 * on the LCD.
 *
 * This task will exit when the robot is enabled and autonomous or opcontrol
 * starts.
 */
void competition_initialize() {}

/**
 * Runs the user autonomous code. This function will be started in its own task
 * with the default priority and stack size whenever the robot is enabled via
 * the Field Management System or the VEX Competition Switch in the autonomous
 * mode. Alternatively, this function may be called in initialize or opcontrol
 * for non-competition testing purposes.
 *
 * If the robot is disabled or communications is lost, the autonomous task
 * will be stopped. Re-enabling the robot will restart the task, not re-start it
 * from where it left off.
 */
void autonomous() {}

/**
 * Runs the operator control code. This function will be started in its own task
 * with the default priority and stack size whenever the robot is enabled via
 * the Field Management System or the VEX Competition Switch in the operator
 * control mode.
 *
 * If no competition control is connected, this function will run immediately
 * following initialize().
 *
 * If the robot is disabled or communications is lost, the
 * operator control task will be stopped. Re-enabling the robot will restart the
 * task, not resume it from where it left off.
 */
#define LEFT_WHEELS_PORT 1
#define RIGHT_WHEELS_PORT -2
#define ARM_PORT 8
#define CLAW_PORT 3

#pragma clang diagnostic push
#pragma clang diagnostic ignored "-Wmissing-noreturn"
void opcontrol() {
    auto chassisPtr = ChassisControllerFactory::createPtr(LEFT_WHEELS_PORT, RIGHT_WHEELS_PORT);
    cout << "Chassis controller set up" << endl;

    pros::Motor arm (ARM_PORT, MOTOR_GEARSET_36); // The arm motor has the 100rpm (red) gearset
    pros::Motor claw (CLAW_PORT, MOTOR_GEARSET_36);
    pros::Controller master (CONTROLLER_MASTER);

    arm.set_brake_mode(pros::E_MOTOR_BRAKE_HOLD);
    claw.set_brake_mode(pros::E_MOTOR_BRAKE_HOLD);



    while (true) {
        /**
         * This will do tank drive
         */
        // left_wheels.move(master.get_analog(ANALOG_LEFT_Y));
        // right_wheels.move(master.get_analog(ANALOG_RIGHT_Y));

        int power = master.get_analog(ANALOG_RIGHT_Y);
        int turn = master.get_analog(ANALOG_LEFT_Y);
        chassisPtr->tank(power, turn);

        if (master.get_digital(DIGITAL_R1)) {
            arm.move_velocity(10); // This is 100 because it's a 100rpm motor
            std::cerr << "asdfadsf" << endl;
            std::cout << "bljnadslfn" << endl;
        }
        else if (master.get_digital(DIGITAL_R2)) {
            arm.move_velocity(-100);
        }
        else {
            arm.move_velocity(0);
        }

        if (master.get_digital(DIGITAL_L1)) {
            claw.move_velocity(100);
        }
        else if (master.get_digital(DIGITAL_L2)) {
            claw.move_velocity(-100);
        }
        else {
            claw.move_velocity(0);
        }

        pros::delay(2);
    }
}
#pragma clang diagnostic pop
#include "main.h"
#include "constants.h"
#include "tasks.h"

using namespace okapi;


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
void autonomous() {
    Motor m1(LEFT_MOTOR_PORT);
    Motor m2(RIGHT_MOTOR_PORT);
    m1.set_brake_mode(pros::E_MOTOR_BRAKE_BRAKE);
    m2.set_brake_mode(pros::E_MOTOR_BRAKE_BRAKE);

    int timeout = 10;
    pros::Task myTask(intake_task_fn, (void*) timeout, "My Task");

    auto myChassis = ChassisControllerFactory::createPtr(
            m1, // Left motors
            m2,   // Right motors
            AbstractMotor::gearset::green, // Torque gearset
            {4_in, 12.5_in} // 4 inch wheels, 12.5 inch wheelbase width
    );

    auto profileController = AsyncControllerFactory::motionProfile(
            1.0,  // Maximum linear velocity of the Chassis in m/s
            0.5,  // Maximum linear acceleration of the Chassis in m/s/s
            1.5, // Maximum linear jerk of the Chassis in m/s/s/s
            *myChassis // Chassis Controller
    );
    profileController.generatePath({
        Point{0_ft, 0_ft, 0_deg},
        Point{49_in, -59_in, 90_deg}},
                "A" // Profile name
    );

    profileController.setTarget("A");
    profileController.waitUntilSettled();
}

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

#pragma clang diagnostic push
#pragma clang diagnostic ignored "-Wmissing-noreturn"
void opcontrol() {
    std::shared_ptr<ChassisControllerIntegrated> chassisPtr = ChassisControllerFactory::createPtr(LEFT_MOTOR_PORT, RIGHT_MOTOR_PORT);
    pros::Motor intake_1(INTAKE_MOTOR_PORT_LEFT);
    pros::Motor intake_2(INTAKE_MOTOR_PORT_RIGHT);
    pros::Controller master(pros::E_CONTROLLER_MASTER);

    double intakeVel = 0;
    double rightX;
    double rightY;
    double leftX;
    double leftY;

#if (AUTO_DEBUG == 1)
    bool should_continue = true;
    while (should_continue) {
        if (master.get_digital(pros::E_CONTROLLER_DIGITAL_A))
            autonomous();
        else if (master.get_digital(pros::E_CONTROLLER_DIGITAL_B))
            should_continue = false;
    }
#else
    while (true) {
        rightX = master.get_analog(pros::E_CONTROLLER_ANALOG_RIGHT_X) / 127.0;
        rightY = master.get_analog(pros::E_CONTROLLER_ANALOG_RIGHT_Y) / 127.0;
        leftX = master.get_analog(pros::E_CONTROLLER_ANALOG_LEFT_X) / 127.0;
        leftY = master.get_analog(pros::E_CONTROLLER_ANALOG_LEFT_Y) / 127.0;

        if (rightX != 0 || rightY != 0)
            chassisPtr->arcade(rightY, rightX);
        else {
            chassisPtr->forward(leftY); /// TODO: Make this less sensitive (i.e. slower) than right stick analog
            chassisPtr->right(leftX);
        }

        if (master.get_digital(INTAKE_BUTTON))
            intakeVel = MOTOR_MOVE_MAX;
        else if (master.get_digital(OUTTAKE_BUTTON))
            intakeVel = -MOTOR_MOVE_MAX;
        else
            intakeVel = 0;

        intake_1.move(intakeVel);
        intake_2.move(intakeVel);
    }
#endif
}
#pragma clang diagnostic pop
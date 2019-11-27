#include "main.h"

#include "smc/robot.h"
#include "smc/tasks.h"

using namespace okapi;

/// Begin forward declaration block
std::shared_ptr<okapi::AsyncMotionProfileController> robot::profile_controller;
std::shared_ptr<okapi::ChassisControllerIntegrated> robot::chassis;
/// End forward declaration block


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
    robot::chassis = ChassisControllerFactory::createPtr(
            okapi::MotorGroup{robot::RIGHT_MOTOR_PORT},
            okapi::MotorGroup{robot::LEFT_MOTOR_PORT},
            AbstractMotor::gearset::green, {4_in, 12.5_in}
    );
    robot::profile_controller = std::make_shared<AsyncMotionProfileController>(
            TimeUtilFactory::create(),
            1.0, 0.5, 1.5,
            robot::chassis->getChassisModel(),
            robot::chassis->getChassisScales(),
            robot::chassis->getGearsetRatioPair()
    );

    robot::chassis->setBrakeMode(okapi::Motor::brakeMode::brake);
    robot::profile_controller->generatePath({
        Point{0_ft, 0_ft, 0_deg},
        Point{49_in, -59_in, 90_deg}},
                "A" // Profile name
    );
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
    int timeout = 10;
    pros::Task myTask(intake_task_fn, (void*) &timeout, "My Task");

    robot::profile_controller->setTarget("A");
    robot::profile_controller->waitUntilSettled();
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
    pros::Motor intake_1(robot::INTAKE_MOTOR_PORT_LEFT);
    pros::Motor intake_2(robot::INTAKE_MOTOR_PORT_RIGHT);
    pros::Controller master(pros::E_CONTROLLER_MASTER);

    double intakeVel = 0;

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
        drive::opControl(master);

        if (master.get_digital(bindings::INTAKE_BUTTON))
            intakeVel = constants::MOTOR_MOVE_MAX;
        else if (master.get_digital(bindings::OUTTAKE_BUTTON))
            intakeVel = -constants::MOTOR_MOVE_MAX;
        else
            intakeVel = 0;

        intake_1.move(intakeVel);
        intake_2.move(intakeVel);
    }
#endif
}
#pragma clang diagnostic pop
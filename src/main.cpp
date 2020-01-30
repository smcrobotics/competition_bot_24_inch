#include <unistd.h>
#define chdir f_chdir


#include "main.h"

#include "smc/robot.h"
#include "smc/tasks.h"
#include "smc/util/Binding.h"

using namespace okapi;
using std::cout;
using std::endl;

typedef okapi::ControllerButton Button;

/* Begin forward declaration block */
std::shared_ptr<okapi::AsyncMotionProfileController> robot::profile_controller;
std::shared_ptr<okapi::ChassisController> robot::chassis;
/* End forward declaration block */


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
    robot::chassis =
            ChassisControllerBuilder().withMotors(
                    okapi::MotorGroup{robot::BACK_LEFT_DRIVE_MOTOR_PORT, robot::FRONT_LEFT_DRIVE_MOTOR_PORT},
                    okapi::MotorGroup{robot::BACK_RIGHT_DRIVE_MOTOR_PORT, robot::FRONT_RIGHT_DRIVE_MOTOR_PORT})
            .withDimensions(AbstractMotor::gearset::green, ChassisScales{{4_in, 24_in}, okapi::imev5GreenTPR})
            .build();

    robot::profile_controller = okapi::AsyncMotionProfileControllerBuilder()
            .withLimits({1.0, 0.5, 1.5})
            .withOutput(robot::chassis)
            .buildMotionProfileController();


    robot::profile_controller->generatePath({
        {0_ft, 0_ft, 0_deg},
        {12_in, 12_in, 0_deg}},"A" // Profile name
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
//    int timeout = 10;
//    pros::Task myTask(intake_task_fn, (void*) &timeout, "My Task");kd

    robot::chassis->getModel()->setBrakeMode(constants::OKAPI_BRAKE);
    robot::profile_controller->setTarget("A");
    robot::profile_controller->waitUntilSettled();
    robot::chassis->getModel()->setBrakeMode(constants::OKAPI_COAST);
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

void initBindings(std::vector<Binding *> & bind_list) {
    // Intake hold binding
    bind_list.emplace_back(new Binding(okapi::ControllerButton(bindings::INTAKE_BUTTON), []() {
        intake::setIntakeVelocity(100);
    }, []() {
        intake::setIntakeVelocity(0);
    }, nullptr));

    // Outtake hold binding
    bind_list.emplace_back(new Binding(okapi::ControllerButton(bindings::OUTTAKE_BUTTON), []() {
        intake::setIntakeVelocity(-100);
    }, []() {
        intake::setIntakeVelocity(0);
    }, nullptr));

    // Arm position bindings
    bind_list.emplace_back(new Binding(Button(bindings::INTAKE_POS_UP), []() {
        intake::moveArmsToPosition(intake::IntakePosition::UP);
    }, nullptr, nullptr));
    bind_list.emplace_back(new Binding(Button(bindings::INTAKE_POS_DOWN), []() {
        intake::moveArmsToPosition(intake::IntakePosition::DOWN);
    }, nullptr, nullptr));

    // Toggle tray binding
    bind_list.emplace_back(new Binding(Button(bindings::TOGGLE_TRAY_POS), tray::togglePosition, nullptr, nullptr));

    // TODO: Remove this before competition
    bind_list.emplace_back(new Binding(okapi::ControllerButton(okapi::ControllerDigital::Y), autonomous, nullptr, nullptr)); // Bind for auto test
    // Note: Auto bind is blocking
    /** End bind block **/
}

#pragma clang diagnostic push
#pragma clang diagnostic ignored "-Wmissing-noreturn"
void opcontrol() {
    okapi::Controller master(okapi::ControllerId::master);
    intake::init();
    tray::init();

    bool isBrake = false;
    std::vector<Binding *> bind_list;
    initBindings(bind_list);
    // Have to do the drive-brake toggle here because it relies on variables local to main()
    bind_list.emplace_back(new Binding(okapi::ControllerButton(bindings::DRIVE_BRAKE_TOGGLE), nullptr,
            [isBrake, master]() mutable {
        isBrake = !isBrake;
        robot::chassis->getModel()->setBrakeMode(isBrake ? constants::OKAPI_BRAKE : constants::OKAPI_COAST);
        master.setText(0, 0, isBrake ? "Brake mode on " : "Brake mode off");
        }, nullptr));

    
    cout << "Initialization finished, entering drive loop" << endl;
    while (true) {
        drive::opControl(master);
        
        for (Binding * b : bind_list)
            b->update();
//        intake::printPos();

        pros::delay(1);
    }

    for (Binding * b : bind_list)
        delete b;

    cout << "Exiting opcontrol()" << endl;
}
#pragma clang diagnostic pop
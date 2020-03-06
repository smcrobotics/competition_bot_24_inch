#include <unistd.h>

#define chdir f_chdir


#include "main.h"

#include "smc/robot.h"
#include "smc/commands.h"
#include "smc/util/Binding.h"
#include "smc/util/util.h"


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
static bool on_right_side = true;
static bool update_lcd_info = true;

void on_right_button() {
    on_right_side = true;
    pros::lcd::clear_line(0);
    pros::lcd::set_text(0, "Auton: Right side");
}

void on_left_button() {
    on_right_side = false;
    pros::lcd::clear_line(0);
    pros::lcd::set_text(0, "Auton: Left side");
}

void on_center_button() {
    update_lcd_info = !update_lcd_info;
}

/**
 * Runs initialization code. This occurs as soon as the program is started.
 *
 * All other competition modes are blocked by initialize; it is recommended
 * to keep execution time for this mode under a few seconds.
 */
void initialize() {
    pros::lcd::initialize();
    pros::lcd::register_btn0_cb(on_left_button);
    pros::lcd::register_btn2_cb(on_right_button);
    pros::lcd::register_btn1_cb(on_center_button);

    pros::lcd::set_text(0, "Auton: Right Side");

    robot::chassis =
            ChassisControllerBuilder().withMotors(
                    okapi::MotorGroup{robot::BACK_LEFT_DRIVE_MOTOR_PORT, robot::FRONT_LEFT_DRIVE_MOTOR_PORT},
                    okapi::MotorGroup{robot::BACK_RIGHT_DRIVE_MOTOR_PORT, robot::FRONT_RIGHT_DRIVE_MOTOR_PORT})
            .withDimensions(AbstractMotor::gearset::green, ChassisScales{{4_in, 16.1_in}, okapi::imev5GreenTPR})
            .build();

    robot::chassis->getModel()->setBrakeMode(constants::OKAPI_BRAKE);

    // These are here to make sure the tray and intake objects are constructed after this point
    subsystems::Intake::getInstance();
    subsystems::Tray::getInstance();

    robot::profile_controller = okapi::AsyncMotionProfileControllerBuilder()
            .withLimits({.1, .1, .1})
            .withOutput(robot::chassis)
            .buildMotionProfileController();


    /*// // first point in list of waypoints gives robot's location with respect to origin
    // // second waypoint is first to be executed
    // // x axis is forward, y axis is to the left */

    // robot::profile_controller->generatePath({
    //     {268.5_cm, 0_cm, 180_deg},
    //     {350.3_cm, 0_cm, 180_deg}}, "forward"
    // );

    // robot::profile_controller->generatePath({
    //     {268.5_cm, 0_cm, 180_deg},
    //     {246.6_cm, 126.7_cm, 0_deg},
    //     {178.6_cm, 126.7_cm, 0_deg},
    //     {67_cm, 126.7_cm, 0_deg}
    // }, "toCubes");

    // robot::profile_controller->generatePath({
    //     {268.5_cm, 0_cm, 180_deg},
    //     {350.3_cm, 0_cm, 180_deg}
    // }, "toScoreZone");

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
    bind_list.emplace_back(new Binding(Button(bindings::INTAKE_BUTTON), []() {
        subsystems::Intake::getInstance()->setIntakeVelocity(70);
    }, []() {
        subsystems::Intake::getInstance()->setIntakeVelocity(0);
    }, nullptr));

    // Outtake hold binding
    bind_list.emplace_back(new Binding(Button(bindings::OUTTAKE_BUTTON), []() {
        subsystems::Intake::getInstance()->setIntakeVelocity(-70);
    }, []() {
        subsystems::Intake::getInstance()->setIntakeVelocity(0);
    }, nullptr));

    // Toggle tray binding
    bind_list.emplace_back(new Binding(Button(bindings::RAISE_TRAY), []() {
        subsystems::Tray::getInstance()->trayMoveManual(60);
    }, []() {
        subsystems::Tray::getInstance()->trayMoveManual(0);
    }, nullptr));

    bind_list.emplace_back(new Binding(Button(bindings::LOWER_TRAY), []() {
        subsystems::Tray::getInstance()->trayMoveManual(-60);
    }, []() {
        subsystems::Tray::getInstance()->trayMoveManual(0);
    }, nullptr));

    bind_list.emplace_back(new Binding(Button(bindings::TOGGLE_TRAY),
        subsystems::Tray::togglePosition, nullptr, nullptr));

//    bind_list.emplace_back(new Binding(Button(bindings::PLACE_STACK),
//        tray::deployTray, nullptr, nullptr));

    bind_list.emplace_back(new Binding(Button(bindings::TOGGLE_INTAKE),
        subsystems::Intake::toggleIntake, nullptr, nullptr));

    // // TODO: Remove this before competition
    // bind_list.emplace_back(new Binding(Button(okapi::ControllerDigital::Y),
    //     autonomous, nullptr, nullptr)); // Bind for auto test
    // Note: Auto bind is blocking
}

#pragma clang diagnostic push
#pragma clang diagnostic ignored "-Wmissing-noreturn"
void opcontrol() {
    const bool DEBUG = false;
    bool isBrake = false;

    okapi::Controller master(okapi::ControllerId::master);

    std::vector<Binding *> bind_list;
    std::vector<subsystems::AbstractSubsystem *> systems;

    systems.push_back(subsystems::Intake::getInstance());
    systems.push_back(subsystems::Tray::getInstance());

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
        double leftY = util::powKeepSign(master.getAnalog(okapi::ControllerAnalog::leftY), 2);
        double rightY = util::powKeepSign(master.getAnalog(okapi::ControllerAnalog::rightY), 2);
        robot::chassis->getModel()->tank(leftY, rightY);
        
        for (Binding * b : bind_list)
            b->update();

        int lcd_line = 1; // start debug info on line 1 an increment for each subsystem
        for (subsystems::AbstractSubsystem * system : systems) {
            system->update();

            if (update_lcd_info)
                system->printLCD(lcd_line);

            if (DEBUG)
                system->printDebug();

            lcd_line++;
        }

        pros::delay(1);
    }

    for (Binding * b : bind_list)
        delete b;

    cout << "Exiting opcontrol()" << endl;
}
#pragma clang diagnostic pop
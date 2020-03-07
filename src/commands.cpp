//
// Created by ariel on 11/15/19.
//

#include "smc/commands.h"

using std::cout;
using std::endl;

namespace commands {
    pros::Task * stack_task;
    bool is_running;

    void deployTray() {
        //TODO: make this interruptable somehow

        subsystems::Intake * intake = subsystems::Intake::getInstance();
        subsystems::Tray * tray = subsystems::Tray::getInstance();

        // lift tray to 30 deg from vertical
        // start opening intakes
        // continue lifting tray slowly while continuing to open intakes
        // back up
        // close intakes

        intake->setIntakeState(subsystems::Intake::IntakeState::OPEN);

        cout << "here 0" << endl;

        pros::delay(1500);
        tray->moveTrayToPosition(subsystems::Tray::TrayPosition::INTER, 50, false);
        pros::delay(750);
        cout << "here 0.5" << endl;
        tray->moveTrayToPosition(subsystems::Tray::UP, 15, false);
        cout << "here 0.75" << endl;
        pros::delay(1500);

        cout << "here 1" << endl;

        double vel = robot::chassis->getModel()->getMaxVelocity();
        robot::chassis->setMaxVelocity(10);
        robot::chassis->moveDistance(-0.5_ft);
        // reset maxVelocity to default val
        robot::chassis->setMaxVelocity(vel);

        cout << "here 2" << endl;


        intake->setIntakeState(subsystems::Intake::IntakeState::CLOSED);
        tray->moveTrayToPosition(subsystems::Tray::DOWN);
        pros::delay(2500);

        robot::can_move = true;
        cout << "Task exit" << endl;
        is_running = false;
    }

    void handleTaskThing() {
        cout << "onPress called" << endl;
        if (stack_task != nullptr && is_running) {
            stack_task->suspend();
            stack_task->remove();

            delete stack_task;
            stack_task = nullptr;

            subsystems::Tray::getInstance()->moveTrayToPosition(subsystems::Tray::DOWN);
            subsystems::Intake::getInstance()->setIntakeState(subsystems::Intake::CLOSED);
            robot::can_move = true;
            is_running = false;
        } else {
            cout << "Starting task" << endl;
            stack_task = new pros::Task(commands::deployTray);
            robot::can_move = false;
            is_running = true;
        }
    }
}

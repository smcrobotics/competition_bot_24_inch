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
        subsystems::Intake * intake = subsystems::Intake::getInstance();
        subsystems::Tray * tray = subsystems::Tray::getInstance();

        intake->setIntakeState(subsystems::Intake::IntakeState::OPEN);

        pros::delay(1500);
        tray->moveTrayToPosition(subsystems::Tray::TrayPosition::INTER, 50, false);
        pros::delay(750);
        tray->moveTrayToPosition(subsystems::Tray::UP, 15, false);
        pros::delay(1500);

        double vel = robot::chassis->getModel()->getMaxVelocity();
        robot::chassis->setMaxVelocity(10);
        robot::chassis->moveDistance(-0.5_ft);
        robot::chassis->setMaxVelocity(vel);

        intake->setIntakeState(subsystems::Intake::IntakeState::CLOSED);
        tray->moveTrayToPosition(subsystems::Tray::DOWN);
        pros::delay(2500);

        robot::can_move = true;
        is_running = false;
    }

    void handleTaskThing() {
        if (stack_task != nullptr && is_running) {
            stack_task->suspend();
            stack_task->remove();

            delete stack_task;
            stack_task = nullptr;

            subsystems::Tray::getInstance()->moveTrayToPosition(subsystems::Tray::DOWN);
            subsystems::Intake::getInstance()->setIntakeState(subsystems::Intake::CLOSED);
            // TODO: do we need to reset max velocity here? If we interrupt when we set max to 10, this could be a problem
            robot::can_move = true;
            is_running = false;
        } else {
            stack_task = new pros::Task(commands::deployTray);
            robot::can_move = false;
            is_running = true;
        }
    }
}

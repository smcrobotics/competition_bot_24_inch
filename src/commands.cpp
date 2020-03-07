//
// Created by ariel on 11/15/19.
//

#include "smc/commands.h"

using std::cout;
using std::endl;

namespace tray {
    void deployTray() {
        //TODO: make this interruptible somehow

        subsystems::Intake * intake = subsystems::Intake::getInstance();
        subsystems::Tray * tray = subsystems::Tray::getInstance();

        // lift tray to 30 deg from vertical
        // start opening intakes
        // continue lifting tray slowly while continuing to open intakes
        // back up
        // close intakes

        cout << "hello 1" << endl;
        
        while (tray->getTrayPosition() < robot::TRAY_MOTOR_INTERMEDIATE_POS) {
            tray->trayMoveManual(60);
            pros::delay(2);
        }

        cout << "hello 2" << endl;
        intake->setIntakeState(subsystems::Intake::IntakeState::OPEN);
        pros::delay(5000);
        tray->moveTrayToPosition(subsystems::Tray::TrayPosition::UP, true);
        pros::delay(5000);
        cout << "hello 3" << endl;
        // pros::delay(5000);
        // double vel = robot::chassis->getModel()->getMaxVelocity();
        // robot::chassis->setMaxVelocity(10);
        // robot::chassis->moveDistance(-1_ft);
        // // reset maxVelocity to default val
        // robot::chassis->setMaxVelocity(vel);
        // pros::delay(2000);

        intake->setIntakeState(subsystems::Intake::IntakeState::CLOSED);
        pros::delay(5000);
        cout << "hello 4" << endl;
    }
}

//
// Created by ariel on 11/15/19.
//

#include "smc/commands.h"

namespace tray {
    void deployTray() {
        subsystems::Intake * intake = subsystems::Intake::getInstance();
        subsystems::Tray * tray = subsystems::Tray::getInstance();
        
        // TODO: fix this, for some reason the velocity is not being set
        intake->setIntakeVelocity(-25);
        tray->moveTrayToPosition(subsystems::Tray::UP);
        pros::delay(1000);
        // intake::setIntakeVelocity(0);
        double vel = robot::chassis->getModel()->getMaxVelocity();
        robot::chassis->setMaxVelocity(10);
        robot::chassis->moveDistance(-1_ft);
        // reset maxVelocity to default val
        robot::chassis->setMaxVelocity(vel);
        pros::delay(2000);
        intake->setIntakeVelocity(0);
    }
}

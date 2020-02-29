//
// Created by ariel on 11/15/19.
//

#include "smc/commands.h"

namespace tray {
    void deployTray() {
        intake::setIntakeVelocity(-20);
        pros::delay(200);
        tray::moveTrayToPosition(tray::TrayPosition::UP, true);
        intake::setIntakeVelocity(-10);
        // intake::setIntakeVelocity(0);
        double vel = robot::chassis->getModel()->getMaxVelocity();
        robot::chassis->setMaxVelocity(10);
        robot::chassis->moveDistance(-0.5_ft);
        // reset maxVelocity to default val
        robot::chassis->setMaxVelocity(vel);
        intake::setIntakeVelocity(0);
    }
}

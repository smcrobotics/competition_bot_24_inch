//
// Created by jeiook on 2/20/20.
//

#include "smc/util/util.h"
#include "smc/robot.h"
#include "smc/subsystems/sideIndicate.h"

namespace sideIndicate {
    Side current_side;

    void init() {
        sideIndicate_limit_switch = util::initLimitSwitch(robot::SIDE_INDICATE_LIMIT_SWITCH_PORT);
        current_side = BLUE;
    }

    bool getSide() {
        if (sideIndicate_limit_switch->isPressed()) {
            current_side = RED;
        }
        return current_side;
    }

    std::unique_ptr<okapi::ADIButton> sideIndicate_limit_switch;
}
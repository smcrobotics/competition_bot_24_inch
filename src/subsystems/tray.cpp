//
// Created by ariel on 11/19/19.
//
#include "smc/util/util.h"
#include "smc/robot.h"
#include "smc/subsystems/tray.h"

namespace tray {
    int limit_timeout;
    TrayPosition current_pos;

    std::unique_ptr<okapi::ADIButton> tray_limit_switch;
    std::unique_ptr<okapi::Motor> tray_position_motor;


    void init() {
        tray_position_motor = util::initMotor(robot::TRAY_POS_MOTOR_PORT);
        tray_limit_switch = util::initLimitSwitch(robot::TRAY_POS_DOWN_LIMIT_SWITCH);

        tray_position_motor->tarePosition();
        current_pos = DOWN;
    }

    void update() {
        if (tray_limit_switch->isPressed() && limit_timeout == 0) {
            tray_position_motor->tarePosition();
            tray_position_motor->moveAbsolute(0, 1);
            current_pos = DOWN;
        }
        else if (limit_timeout > 0)
            limit_timeout--;
    }

    void moveTrayToPosition(TrayPosition pos) {
        if (pos == UP) {
            tray_position_motor->moveAbsolute(robot::TRAY_MOTOR_POS_UP, 120);
            limit_timeout = 40;
            current_pos = UP;
        } else if (pos == DOWN) {
            tray_position_motor->moveAbsolute(0, 120);
            current_pos = DOWN;
        }
    }

    void togglePosition() {
        moveTrayToPosition((TrayPosition) !current_pos);
    }
}
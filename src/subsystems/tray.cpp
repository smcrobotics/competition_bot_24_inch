//
// Created by ariel on 11/19/19.
//
#include "smc/util/util.h"
#include "smc/robot.h"
#include "smc/subsystems/tray.h"

using std::cout;
using std::endl;

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

    void printPos() {
        cout << "[POS] Tray motor position: " << tray_position_motor->getPosition() << endl;
    }

    void moveTrayToPosition(TrayPosition pos, bool blocking) {
        // int motor_velocity = 40;
        if (pos == UP) {
            tray_position_motor->moveAbsolute(robot::TRAY_MOTOR_POS_UP, 40); // TODO: change to constants::AUTO_TRAY_SPEED
            limit_timeout = 200;
            current_pos = UP;
        } else if (pos == DOWN) {
            tray_position_motor->moveAbsolute(0, 40); // TODO: change to constants::AUTO_TRAY_SPEED
            current_pos = DOWN;
        }

        if (blocking) { // choose whether to block other tasks from performing
            while (!tray_position_motor->isStopped())
                pros::delay(10);
        }
    }

    void moveTrayToPosition(TrayPosition pos) {
        moveTrayToPosition(pos, false);
    }

    void setTrayVelocity(int percent) {
        float voltage = ((float) percent / 100.0f) * 12000;
        tray_position_motor->moveVoltage((int) voltage);
    }

    void togglePosition() {
        moveTrayToPosition((TrayPosition) !current_pos, false);
    }
}
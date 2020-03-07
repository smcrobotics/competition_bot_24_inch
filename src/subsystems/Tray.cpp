//
// Created by ariel on 11/19/19.
//
#include "smc/util/util.h"
#include "smc/robot.h"
#include "smc/subsystems/Tray.h"

using std::cout;
using std::endl;

namespace subsystems {
    Tray::Tray() : limit_timeout(0), current_pos(DOWN) {
        tray_position_motor = util::initMotor(robot::TRAY_POS_MOTOR_PORT, AbstractMotor::gearset::red);
        tray_limit_switch = util::initLimitSwitch(robot::TRAY_POS_DOWN_LIMIT_SWITCH);

        tray_position_motor->tarePosition();
    }

    Tray * Tray::getInstance() {
        static Tray tray;
        return &tray;
    }

    void Tray::update() {
        if (tray_limit_switch->isPressed() && limit_timeout == 0) {
            tray_position_motor->tarePosition();
            if (tray_position_motor->getActualVelocity() < 0) {
                tray_position_motor->moveAbsolute(0, 1);
            }
            current_pos = DOWN;
            limit_timeout = 50;
        }
        else if (limit_timeout > 0) {
            limit_timeout--;
        }
    }

    void Tray::printDebug() {
        cout << "[DEBUG][Tray] Tray target: " << tray_position_motor->getTargetPosition() << endl;
        cout << "[DEBUG][Tray] Tray actual: " << tray_position_motor->getPosition() << endl;
    }

    void Tray::printLCD(int line) {
        std::ostringstream out;

        out << "[T] tgt: " << tray_position_motor->getTargetPosition();
        out << ", pos: " << tray_position_motor->getPosition();
        out << ", t'out: " << limit_timeout;

        pros::lcd::clear_line(line);
        pros::lcd::set_text(line, out.str());
    }

    void Tray::moveTrayToPosition(TrayPosition pos, int speed, bool blocking) {
        if (speed < 0)
            return;

        if (pos == UP) {
            tray_position_motor->moveAbsolute(robot::TRAY_MOTOR_POS_UP, speed); // TODO: change to constants::AUTO_TRAY_SPEED
            limit_timeout = 200;
            current_pos = UP;
        } else if (pos == DOWN) {
            tray_position_motor->moveAbsolute(0, speed); // TODO: change to constants::AUTO_TRAY_SPEED
            current_pos = DOWN;
        } else if (pos == INTER) {
            tray_position_motor->moveAbsolute(robot::TRAY_MOTOR_INTERMEDIATE_POS, speed);
            current_pos = INTER;
        }

        if (blocking) { // choose whether to block other tasks from performing
            while (tray_position_motor->getPositionError() > 10)
                pros::delay(5);
        }
    }

    void Tray::moveTrayToPosition(TrayPosition pos, bool blocking) {
        moveTrayToPosition(pos, 60, blocking);
    }

    void Tray::moveTrayToPosition(TrayPosition pos) {
        moveTrayToPosition(pos, false);
    }

    void Tray::trayMoveManual(int motorSpeedPercent) {
        if (!(tray_limit_switch->isPressed() && motorSpeedPercent < 0)) {
            tray_position_motor->moveVoltage((int) (((float) motorSpeedPercent / 100.0f) * 12000));
        }
    }

    void Tray::togglePosition() {
        getInstance()->moveTrayToPosition((TrayPosition) !getInstance()->current_pos);
    }

    int Tray::getTrayPosition() {
        return tray_position_motor->getPosition();
    }
}

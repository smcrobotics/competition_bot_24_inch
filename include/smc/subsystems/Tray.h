//
// Created by ariel on 11/19/19.
//

#ifndef ROBOT_CODE_TRAY_H
#define ROBOT_CODE_TRAY_H

#include "api.h"
#include "okapi/api.hpp"
#include "smc/subsystems/AbstractSubsystem.h"

namespace subsystems {
class Tray : public AbstractSubsystem {
    public:
        enum TrayPosition { UP = 1, DOWN = 0 };

        static Tray * getInstance();
        Tray(const Tray &) = delete;
        void operator=(const Tray & lhs) = delete;

        void update() override;
        void printDebug() override;
        void printLCD(int line) override;

        int getTrayPosition();

        void moveTrayToPosition(TrayPosition pos, bool blocking);
        void moveTrayToPosition(TrayPosition pos);

        void trayMoveManual(int motorSpeedPercent);

        static void togglePosition();

    private:
        Tray();

        TrayPosition current_pos;
        int limit_timeout;

        std::unique_ptr<okapi::ADIButton> tray_limit_switch;
        std::unique_ptr<okapi::Motor> tray_position_motor;
    };
}

#endif //ROBOT_CODE_TRAY_H

//
// Created by ariel on 11/19/19.
//

#ifndef ROBOT_CODE_TRAY_H
#define ROBOT_CODE_TRAY_H

#include "api.h"
#include "okapi/api.hpp"
#include "smc/subsystems/AbstractSubsystem.h"

namespace tray {
    enum TrayPosition { UP = 1, DOWN = 0 };
    extern TrayPosition current_pos;

    void init();
    void update();
    void printPos();

    void moveTrayToPosition(TrayPosition pos, bool blocking);
    void moveTrayToPosition(TrayPosition pos);

    void setTrayVelocity(int percent);
    void togglePosition();

    const int trayPosKP = 1; // TODO: Tune these PID values as well
    const int trayPosKI = 1;
    const int trayPosKD = 1;

    extern int limit_timeout;

    extern std::unique_ptr<okapi::ADIButton> tray_limit_switch;
    extern std::unique_ptr<okapi::Motor> tray_position_motor;
}

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

        void moveTrayToPosition(TrayPosition pos, bool blocking);
        void moveTrayToPosition(TrayPosition pos);

        static void togglePosition();

    private:
        Tray();

        TrayPosition current_pos;
        int limit_timeout;
        bool did_tare;

        std::unique_ptr<okapi::ADIButton> tray_limit_switch;
        std::unique_ptr<okapi::Motor> tray_position_motor;
    };
}

#endif //ROBOT_CODE_TRAY_H

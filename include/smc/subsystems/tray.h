//
// Created by ariel on 11/19/19.
//

#ifndef ROBOT_CODE_TRAY_H
#define ROBOT_CODE_TRAY_H

#include "api.h"
#include "okapi/api.hpp"

namespace tray {
    enum TrayPosition { UP = 1, DOWN = 0 };
    extern TrayPosition current_pos;

    void init();
    void update();

    void moveTrayToPosition(TrayPosition pos);
    void togglePosition();
    void placeStack();

    const int trayPosKP = 1; // TODO: Tune these PID values as well
    const int trayPosKI = 1;
    const int trayPosKD = 1;

    extern int limit_timeout;

    extern std::unique_ptr<okapi::ADIButton> tray_limit_switch;
    extern std::unique_ptr<okapi::Motor> tray_position_motor;
}

#endif //ROBOT_CODE_TRAY_H

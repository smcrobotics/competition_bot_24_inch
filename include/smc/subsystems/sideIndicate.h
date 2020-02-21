//
// Created by jeiook on 2/20/20.
//

#ifndef COMPETITION_BOT_24_INCH_SIDEINDICATE_H
#define COMPETITION_BOT_24_INCH_SIDEINDICATE_H

#include <bits/unique_ptr.h>
#include "okapi/api.hpp"

namespace sideIndicate {
    enum Side {RED = 1, BLUE = 0};
    extern Side current_side;

    void init();
    void update();

    bool getSide();

    extern std::unique_ptr<okapi::ADIButton> sideIndicate_limit_switch;
}

#endif //COMPETITION_BOT_24_INCH_SIDEINDICATE_H
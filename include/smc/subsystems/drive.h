/**
 * \file main.h
 *
 * Contains common definitions and header files used throughout your PROS
 * project.
 *
 * Copyright (c) 2017-2019, Purdue University ACM SIGBots.
 * All rights reserved.
 *
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this
 * file, You can obtain one at http://mozilla.org/MPL/2.0/.
 */

#ifndef _DRIVE_H_
#define _DRIVE_H_

#include "main.h"

namespace drive {
    /**
     * Creates relevant objects for the drivetrain subsystem and starts their tasks.
     */
    void init();

    void opControl(double right_x, double right_y, double left_x);
}

#endif
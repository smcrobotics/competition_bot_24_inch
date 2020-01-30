#include "main.h"

#include "smc/subsystems/drive.h"
#include "smc/util/util.h"
#include "smc/util/constants.h"

#include <math.h>

using namespace okapi;

namespace drive {

    void init() {}

    void opControl(okapi::Controller & master) {
        double leftAnalogY = master.getAnalog(okapi::ControllerAnalog::leftY) / 127.0;
        double leftAnalogX = master.getAnalog(okapi::ControllerAnalog::leftX) / 127.0;
        double rightAnalogY = master.getAnalog(okapi::ControllerAnalog::rightY) / 127.0;
        double rightAnalogX = master.getAnalog(okapi::ControllerAnalog::rightX) / 127.0;

        double rightY = pow(abs(rightAnalogY), 1.5) * rightAnalogY / abs(rightAnalogY);
        double rightX = pow(abs(rightAnalogX), 1.5) * rightAnalogX / abs(rightAnalogX);
        double leftX = pow(abs(leftAnalogX), 1.5) * leftAnalogX / abs(leftAnalogX);
        double leftY = pow(abs(leftAnalogY), 1.5) * leftAnalogY / abs(leftAnalogY);

        robot::chassis->getModel()->tank(leftY, rightY);
    }
}
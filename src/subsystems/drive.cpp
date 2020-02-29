#include "main.h"

#include "smc/subsystems/drive.h"
#include "smc/util/util.h"
#include "smc/util/constants.h"

#include <math.h>

using namespace okapi;

using std::cout;
using std::endl;

namespace drive {

    void init() {}

    void opControl(okapi::Controller & master) {
        double leftAnalogY = master.getAnalog(okapi::ControllerAnalog::leftY);
        double leftAnalogX = master.getAnalog(okapi::ControllerAnalog::leftX);
        double rightAnalogY = master.getAnalog(okapi::ControllerAnalog::rightY);
        double rightAnalogX = master.getAnalog(okapi::ControllerAnalog::rightX);

        double rightY = pow(abs(rightAnalogY), 2) * rightAnalogY / abs(rightAnalogY);
        double rightX = pow(abs(rightAnalogX), 2) * rightAnalogX / abs(rightAnalogX);
        double leftX = pow(abs(leftAnalogX), 2) * leftAnalogX / abs(leftAnalogX);
        double leftY = pow(abs(leftAnalogY), 2) * leftAnalogY / abs(leftAnalogY);

        robot::chassis->getModel()->tank(leftY, rightY);
    }
}
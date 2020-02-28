//
// Created by ariel on 2/27/20.
//

#ifndef COMPETITION_BOT_24_INCH_ABSTRACTSUBSYSTEM_H
#define COMPETITION_BOT_24_INCH_ABSTRACTSUBSYSTEM_H

namespace subsystems {
    class AbstractSubsystem {
    public:
        virtual void update() = 0;

        virtual void printDebug() = 0;

        virtual void printLCD(int line) = 0;
    };
}


#endif //COMPETITION_BOT_24_INCH_ABSTRACTSUBSYSTEM_H

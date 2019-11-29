//
// Created by ariel on 11/28/19.
//

#ifndef ROBOT_CODE_BINDING_H
#define ROBOT_CODE_BINDING_H


#include <functional>
#include "okapi/api.hpp"

typedef std::function<void (void)> CallbackFn;

class Binding {
public:
    Binding(const okapi::ControllerButton & button, CallbackFn callback);
    Binding(okapi::ControllerButton button, CallbackFn callback, int timeout);

    void update();
private:
    okapi::ControllerButton m_button;
    const CallbackFn m_callback;
    const int m_timeout;
    int m_timeout_count;
};


#endif //ROBOT_CODE_BINDING_H

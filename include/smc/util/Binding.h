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
    Binding(okapi::ControllerButton  button, CallbackFn onPress, CallbackFn onRelease, CallbackFn onPressedUpdate);

    void update();
    void onUpdatePressed(CallbackFn & callback);
    void onPress(CallbackFn & callback);
    void onReleased(CallbackFn & callback);
private:
    okapi::ControllerButton m_button;
    CallbackFn m_updateCallback;
    CallbackFn m_pressedCallback;
    CallbackFn m_releasedCallback;
};


#endif //ROBOT_CODE_BINDING_H

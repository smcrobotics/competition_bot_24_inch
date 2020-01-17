//
// Created by ariel on 11/28/19.
//

#include "smc/util/Binding.h"

#include <utility>


Binding::Binding(okapi::ControllerButton button, CallbackFn onPress,
                 CallbackFn onRelease, CallbackFn onPressedUpdate) : m_button(std::move(button)),
                 m_updateCallback(std::move(onPressedUpdate)), m_pressedCallback(std::move(onPress)), m_releasedCallback(std::move(onRelease)),
                 was_pressed(false) {}

void Binding::update() {
    if (ignore_tick > 0) {
        ignore_tick--;
        return;
    }

    if (m_releasedCallback != nullptr && m_button.changedToReleased()) { // TODO: This doesn't work correctly, we're running whenever not pressed
        m_releasedCallback();
        was_pressed = false;
        ignore_tick = 100;

        std::cout << "asdlkfjasfd" << std::endl;
    }
    if ( m_updateCallback != nullptr && m_button.isPressed()) {
        m_updateCallback();
        was_pressed = true;
    }
    if (m_pressedCallback != nullptr && m_button.changedToPressed() && !was_pressed) {
        m_pressedCallback();
        was_pressed = true;
        std::cout << "wpoieurpoiewq" << std::endl;
    }


//    if (m_releasedCallback != nullptr && !m_button.isPressed() && !was_pressed)
//        std::cout << "bohlsach" << std::endl;
}

void Binding::onPress(CallbackFn & callback) {
    m_pressedCallback = callback;
}

void Binding::onReleased(CallbackFn &callback) {
    m_releasedCallback = callback;
}

void Binding::onUpdatePressed(CallbackFn &callback) {
    m_updateCallback = callback;
}
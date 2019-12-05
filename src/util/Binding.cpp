//
// Created by ariel on 11/28/19.
//

#include "smc/util/Binding.h"

#include <utility>


Binding::Binding(okapi::ControllerButton button, CallbackFn onPress,
                 CallbackFn onRelease, CallbackFn onPressedUpdate) : m_button(std::move(button)),
                 m_updateCallback(std::move(onPressedUpdate)), m_pressedCallback(std::move(onPress)), m_releasedCallback(std::move(onRelease))
                 {}

void Binding::update() {
    if ( m_updateCallback != nullptr && m_button.isPressed())
        m_updateCallback();
    if (m_pressedCallback != nullptr && m_button.changedToPressed())
        m_pressedCallback();
    if (m_releasedCallback != nullptr && m_button.changedToReleased())
        m_releasedCallback();
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
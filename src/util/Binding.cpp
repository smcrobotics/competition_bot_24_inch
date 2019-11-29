//
// Created by ariel on 11/28/19.
//

#include "smc/util/Binding.h"

#include <utility>


Binding::Binding(const okapi::ControllerButton &bind, CallbackFn callback) :
    Binding(bind, callback, 0) {}

Binding::Binding(okapi::ControllerButton bind, CallbackFn callback, int timeout) :
        m_button(std::move(bind)), m_callback(std::move(callback)), m_timeout(timeout) {
    m_timeout_count = 0;
}

void Binding::update() {
    if (m_button.isPressed() && m_timeout_count == 0) {
        m_callback();
        m_timeout_count = m_timeout;
    }

    if (m_timeout_count > 0) m_timeout_count--;
}
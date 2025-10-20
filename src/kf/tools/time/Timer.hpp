#pragma once

#include <Arduino.h>

#include <kf/units.hpp>

namespace kf::tools {

/// @brief Таймер
struct Timer {

    /// @brief Период срабатывания таймера
    Microseconds period;

private:
    Microseconds last{0};

public:
    explicit Timer(Milliseconds period) :
        period{period} {}

    /// @brief Прошел ли период
    bool ready() {
        const auto now = millis();
        const auto delta = now - last;

        if (delta < period) { return false; }

        last = now;

        return true;
    }
};

}// namespace kf::tools

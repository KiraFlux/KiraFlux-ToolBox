#pragma once

#include <Arduino.h>

#include <kf/units.hpp>

namespace kf::tools {

/// @brief Хронометр
struct Chronometer final {

private:
    /// @brief Момент предыдущего измерения
    Microseconds last{micros()};

public:
    /// @brief Рассчитать дельту между вызовами
    Seconds calc() noexcept {
        const auto now = micros();
        const auto delta = now - last;
        last = now;
        return static_cast<decltype(calc())>(delta) * 1e-6f;
    }
};

}// namespace kf::tools

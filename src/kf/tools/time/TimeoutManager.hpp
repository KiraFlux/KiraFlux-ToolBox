#pragma once

#include <Arduino.h>

#include <kf/units.hpp>

namespace kf::tools {

/// @brief Служба для отслеживания момента истечения допустимого таймаута
struct TimeoutManager final {

private:
    /// @brief Таймаут
    Milliseconds timeout;

    /// @brief Момент следующего таймаута
    Milliseconds next_timeout{0};

public:
    explicit TimeoutManager(Milliseconds timeout_duration) :
        timeout{timeout_duration} {}

    /// @brief Обновление таймаута
    void update() {
        next_timeout = millis() + timeout;
    }

    /// @brief Проверка истечения таймаута
    /// @returns true - таймаут просрочен
    [[nodiscard]] inline bool expired() const { return millis() >= next_timeout; }
};

}// namespace kf::tools

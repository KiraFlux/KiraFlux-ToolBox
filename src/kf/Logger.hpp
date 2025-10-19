#pragma once

#include <Arduino.h>
#include <kf/tools/meta/Singleton.hpp>


namespace kf {

/// Logger
struct Logger final : tools::Singleton<Logger> {
    friend struct Singleton<Logger>;

    using WriteFunction = void (*)(const char *, size_t);

    WriteFunction writer{nullptr};

    void log(const char *level, const char *function, const char *format, ...) const {
        if (writer == nullptr) { return; }

        char buffer[128];
        size_t pos = 0;

        // Форматируем префикс
        int prefix_len = snprintf(buffer, sizeof(buffer),
                                  "[%lu|%s|%s] ",
                                  millis(), level, function);

        if (prefix_len > 0) {
            pos = min(static_cast<size_t>(prefix_len), sizeof(buffer) - 1);
        }

        // Форматируем основное сообщение
        if (pos < sizeof(buffer)) {
            va_list args;
            va_start(args, format);
            int msg_len = vsnprintf(buffer + pos,
                                    sizeof(buffer) - pos,
                                    format,
                                    args);
            va_end(args);

            if (msg_len > 0) {
                pos += min(static_cast<size_t>(msg_len), sizeof(buffer) - pos - 1);
            }
        }

        // Добавляем перевод строки
        if (pos < sizeof(buffer) - 1) {
            buffer[pos] = '\n';
            pos++;
        } else {
            // Если не хватило места - заменяем последний символ
            buffer[sizeof(buffer) - 2] = '\n';
            pos = sizeof(buffer) - 1;
        }

        writer(buffer, pos);
    }
};

}

/// Debug
#define kf_Logger_level_debug 0
/// Info
#define kf_Logger_level_info 1
/// Warn
#define kf_Logger_level_warn 2
/// Error
#define kf_Logger_level_error 3
/// Fatal
#define kf_Logger_level_fatal 4
/// None (Disable)
#define kf_Logger_level_none 5

#if not defined(kf_Logger_level)
#define kf_Logger_level kf_Logger_level_debug
#endif

#if kf_Logger_level_debug >= kf_Logger_level
#define kf_Logger_debug(...)   kf::Logger::instance().log("Debug",   __PRETTY_FUNCTION__, __VA_ARGS__)
#else
#define kf_Logger_debug(...)
#endif

#if kf_Logger_level_info >= kf_Logger_level
#define kf_Logger_info(...)   kf::Logger::instance().log("Info",   __PRETTY_FUNCTION__, __VA_ARGS__)
#else
#define kf_Logger_info(...)
#endif

#if kf_Logger_level_warn >= kf_Logger_level
#define kf_Logger_warn(...)   kf::Logger::instance().log("Warn",   __PRETTY_FUNCTION__, __VA_ARGS__)
#else
#define kf_Logger_warn(...)
#endif

#if kf_Logger_level_error >= kf_Logger_level
#define kf_Logger_error(...)   kf::Logger::instance().log("Error",   __PRETTY_FUNCTION__, __VA_ARGS__)
#else
#define kf_Logger_error(...)
#endif

#if kf_Logger_level_fatal >= kf_Logger_level
#define kf_Logger_fatal(...)   kf::Logger::instance().log("Fatal",   __PRETTY_FUNCTION__, __VA_ARGS__)
#else
#define kf_Logger_fatal(...)
#endif

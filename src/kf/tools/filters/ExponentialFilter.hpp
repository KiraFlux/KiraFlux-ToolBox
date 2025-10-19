#pragma once

namespace kf::tools {

/// Экспоненциальный фильтр
template<typename T> struct ExponentialFilter {
    float k;
    T filtered;

    constexpr explicit ExponentialFilter(float k, T init_value = T{}) :
        k{k}, filtered{init_value} {}

    const T &calc(const T &value) {
        filtered += (value - filtered) * k;
        return filtered;
    }
};

}

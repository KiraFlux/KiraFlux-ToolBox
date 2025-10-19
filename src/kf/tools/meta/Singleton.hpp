#pragma once

namespace kf::tools {

/// Полная реализация шаблона проектирования "Одиночка"
template<typename T> struct Singleton {

    /// Получить ссылку на единственный экземпляр
    static T &instance() {
        static T instance{};
        return instance;
    }

    // Запрет копирования
    Singleton(const Singleton &) = delete;

    // Запрет присваивания
    Singleton &operator=(const Singleton &) = delete;

protected:
    // Скрытие конструктора по умолчанию (Гарантия единственного экземпляра)
    Singleton() = default;

    // Скрытие деструктора (Гарантия валидности экземпляра всегда)
    ~Singleton() = default;
};

}// namespace djc

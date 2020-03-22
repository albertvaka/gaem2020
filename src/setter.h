#pragma once

#include <functional>

template <typename T>
struct setter
{
    setter& operator=(T const& v) {
        setf(v);
        return *this;
    }

    std::function<void(T)> setf;
    setter(std::function<void(T)> f) { setf = f; }
};

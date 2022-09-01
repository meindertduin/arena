#pragma once

#include <tuple>

namespace types {
    template<typename T>
    struct member_function_traits;

    template<typename R, typename T, typename... Args>
    struct member_function_traits<R(T::*)(Args...)> {
        static const std::size_t n_args = sizeof...(Args);
        using result_type = R;
        using instance_type = T;

        using arg_tuple = std::tuple<Args...>;
        using first_argument = std::tuple_element_t<0, arg_tuple>;
    };
}

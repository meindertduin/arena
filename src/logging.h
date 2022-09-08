#pragma once

#include <string>
#include <stdexcept>

inline constexpr std::string& replace_str_format(std::string &str, const std::string& arg) {
    auto pos = str.find("%s");
    str.replace(pos, 2, arg);
    return str;
}

template<typename ...Args>
inline void log_error(const std::string &error, Args... args) {
    throw std::runtime_error((replace_str_format(error, args), ...));
}

template<>
inline void log_error(const std::string &error) {
    throw std::runtime_error(error);
}

#define THROW_ERROR(...) log_error(__VA_ARGS__);
    

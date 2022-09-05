#pragma once

#include <string>
#include <stdexcept>

constexpr std::string& replace_str_format(std::string &str, std::string arg) {
    auto pos = str.find_first_of("%s");
    str.replace(pos, 2, arg);
    return str;
}

template<typename ...Args>
void log_error(std::string error, Args... args) {
    throw std::runtime_error((replace_str_format(error, args), ...));
}

template<>
void log_error(std::string error) {
    throw std::runtime_error(error);
}

#define THROW_ERROR(...) log_error(__VA_ARGS__);
    

#pragma once

#include <string>
#include <stdexcept>
#include <iostream>

static std::string EscSeqResetColor = "\x1b[0m";
static std::string EscSeqFgGreen = "\x1b[92m";
static std::string EscSeqFgYellow = "\x1b[93m";

inline void color_write_console(std::string msg, const std::string &color_sequence) {
    auto str = color_sequence + msg + EscSeqResetColor;
    std::cout << str << std::endl;
}

inline constexpr std::string& replace_str_format(std::string &str, std::string arg) {
    auto pos = str.find("%s");
    str.replace(pos, 2, arg);
    return str;
}

template<typename ...Args>
inline void log_error(std::string error, Args... args) {
    throw std::runtime_error((replace_str_format(error, args), ...));
}

template<>
inline void log_error(const std::string error) {
    throw std::runtime_error(error);
}

inline void debug(const std::string& msg) {
    color_write_console(msg, EscSeqFgGreen);
}

template<typename ...Args>
inline void debug(std::string msg, Args... args) {
    color_write_console((replace_str_format(msg, args), ...), EscSeqFgGreen);
}

inline void warning(const std::string &msg) {
    color_write_console(msg, EscSeqFgYellow);
}

template<typename ...Args>
inline void warning(std::string msg, Args... args) {
    color_write_console((replace_str_format(msg, args), ...), EscSeqFgYellow);
}


#define THROW_ERROR(...) log_error(__VA_ARGS__);
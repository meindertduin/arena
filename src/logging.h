#pragma once

#include <string>
#include <stdexcept>
#include <iostream>

static std::string EscSeqResetColor = "\x1b[0m";
static std::string EscSeqFgGreen = "\x1b[92m";
static std::string EscSeqFgYellow = "\x1b[93m";

class Logger {
public:
    template<typename ...Args>
    static inline void log_error(std::string error, Args... args) {
        throw std::runtime_error((replace_str_format(error, args), ...));
    }

    static inline void log_error(const std::string& error) {
        throw std::runtime_error(error);
    }

    static inline void debug(const std::string& msg) {
        color_write_console(msg, EscSeqFgGreen);
    }

    template<typename ...Args>
    static inline void debug(std::string msg, Args... args) {
        color_write_console((replace_str_format(msg, args), ...), EscSeqFgGreen);
    }

    static inline void warning(const std::string &msg) {
        color_write_console(msg, EscSeqFgYellow);
    }

    template<typename ...Args>
    static inline void warning(std::string msg, Args... args) {
        color_write_console((replace_str_format(msg, args), ...), EscSeqFgYellow);
    }
private:
    static inline void color_write_console(std::string msg, const std::string &color_sequence) {
        auto str = color_sequence + msg + EscSeqResetColor;
        std::cout << str << std::endl;
    }

    static inline constexpr std::string& replace_str_format(std::string &str, std::string arg) {
        auto pos = str.find("%s");
        str.replace(pos, 2, arg);
        return str;
    }
};

#define THROW_ERROR(...) Logger::log_error(__VA_ARGS__)


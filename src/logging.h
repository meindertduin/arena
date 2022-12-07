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
        log(LogStatus::Error, (replace_str_format(error, args), ...));
        throw std::runtime_error("An error has occurred while running this program");
    }

    static inline void log_error(const std::string& error) {
        log(LogStatus::Error, error);
        throw std::runtime_error("An error has occurred while running this program");
    }

    static inline void debug(const std::string& message) {
        log(LogStatus::Debug, message);
    }

    template<typename ...Args>
    static inline void debug(std::string msg, Args... args) {
        color_write_console((replace_str_format(msg, args), ...), EscSeqFgGreen);
    }

    static inline void warning(const std::string &message) {
        log(LogStatus::Warning, message);
    }

    template<typename ...Args>
    static inline void warning(std::string message, Args... args) {
        log(LogStatus::Warning, (replace_str_format(message, args), ...));
    }
private:
    enum class LogStatus {
        Info,
        Warning,
        Debug,
        Error,
    };

    static inline constexpr std::string& replace_str_format(std::string &str, std::string arg) {
        auto pos = str.find("%s");
        str.replace(pos, 2, arg);
        return str;
    }

    static inline void log(LogStatus status, std::string message) {
        switch (status) {
            case LogStatus::Info:
                message = "[info] " + message;
                break;
            case LogStatus::Warning:
                message = EscSeqFgYellow + "[warning] " + message + EscSeqResetColor;
                break;
            case LogStatus::Error:
                message = EscSeqFgYellow + "[error] " + message + EscSeqResetColor;
                break;
            case LogStatus::Debug:
                message = EscSeqFgGreen + "[debug] " + message + EscSeqResetColor;
                break;
        }

        std::cout << message << std::endl;
    }
};

#define THROW_ERROR(...) Logger::log_error(__VA_ARGS__)


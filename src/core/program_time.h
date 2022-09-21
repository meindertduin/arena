#pragma once

#include <chrono>

namespace core {
    inline static auto ProgramStartTime = std::chrono::system_clock::now();

    void delay(int ms);
    double program_time_ms();
}

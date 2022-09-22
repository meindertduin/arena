#pragma once

#include <chrono>

namespace core {
    using TimePoint = std::chrono::system_clock::time_point;
    using DurationMs = std::chrono::duration<double, std::milli>;

    inline static auto ProgramStartTime = std::chrono::system_clock::now();

    void delay(int ms);
    double program_time_ms();

    class Timer {
    public:
        void start();
        void stop();

        [[nodiscard]] int difference_ms() const;
    private:
        TimePoint start_time;
        int duration_ms {0};
    };
}

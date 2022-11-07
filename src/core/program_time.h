#pragma once

#include <chrono>
#include <atomic>

namespace core {
    static constexpr int TickTimeMs = 10;
    static std::atomic<unsigned long> TotalTicks {0};

    using TimePoint = std::chrono::system_clock::time_point;
    using DurationMs = std::chrono::duration<double, std::milli>;

    inline static auto ProgramStartTime = std::chrono::system_clock::now();

    void delay(int ms);
    double program_time_ms();

    class Timer {
    public:
        void start();
        [[nodiscard]] int get_time_ms() const;
        void stop();

        [[nodiscard]] int difference_ms() const;
    private:
        TimePoint start_time;
        int duration_ms {0};
    };
}

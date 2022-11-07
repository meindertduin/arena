#include "program_time.h"

#include <thread>

namespace core {
    void delay(int ms) {
       std::this_thread::sleep_for(std::chrono::milliseconds(ms));
    }

    double program_time_ms() {
        DurationMs timespan = std::chrono::system_clock::now() - ProgramStartTime;
        return timespan.count();
    }

    void Timer::start() {
        duration_ms = 0;
        start_time = std::chrono::system_clock::now();
    }

    int Timer::get_time_ms() const {
        auto current_time = std::chrono::system_clock::now();
        DurationMs difference = current_time - start_time;
        return static_cast<int>(difference.count());
    }

    void Timer::stop() {
        duration_ms = get_time_ms();
    }

    int Timer::difference_ms() const {
        return duration_ms;
    }
}
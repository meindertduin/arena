#include "program_time.h"

#include <thread>

namespace core {
    void delay(int ms) {
       std::this_thread::sleep_for(std::chrono::milliseconds(ms));
    }

    double program_time_ms() {
        std::chrono::duration<double, std::milli> timespan = std::chrono::system_clock::now() - ProgramStartTime;
        return timespan.count();
    }
}
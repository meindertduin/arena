#pragma once

#include "program_time.h"

class Application {
public:
    void initialize();
    void run();

    ~Application();
private:
    bool m_editor { true };
    core::Timer m_program_timer;
};
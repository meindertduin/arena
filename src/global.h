#pragma once

#include "core/window.h"

struct Global {
    core::Window *window;

    ~Global() {
        delete window;
    }
} global;

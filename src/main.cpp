#include <stdio.h>

#include "global.h"

int main () {
    auto window_options = core::WindowOptions {
        .width = 1280,
        .height = 720,
        .window_name = "Arena"
    };

    global.window = new core::Window(window_options);

    while(!global.window->close_requested()) {
        global.window->end_frame();
    }
    return 0;
}

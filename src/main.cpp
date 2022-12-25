#include "global.h"

#include "editor/editor.h"
#include "core/application.h"

Global global;

int main () {
    Application application;
    application.initialize();
    application.run();

    return 0;
}

#pragma once

namespace core {
    class Command {
    public:
        virtual void execute() = 0;
    };
}
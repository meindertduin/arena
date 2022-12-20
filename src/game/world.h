#pragma once

namespace game {
    class IWorld {
    public:
        virtual ~IWorld() = default;
        virtual void update() = 0;
    };
}
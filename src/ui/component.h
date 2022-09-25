#pragma once

#include <string>
#include "../graphics/geometry.h"

namespace ui {
    class UIComponent {
    public:
        int width;
        int height;

        virtual void render() = 0;
    };

    class ButtonComponent : public UIComponent {
    public:
        explicit ButtonComponent(const glm::ivec2 &pos, const glm::ivec2 &size);
        void render() override;
    private:
        std::string text;
        glm::ivec2 pos;
        glm::ivec2 size;

        graphics::GpuPlane background;
        graphics::GpuPlane border;
    };
}
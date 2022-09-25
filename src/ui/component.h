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
        ButtonComponent();

        void render() override;
    private:
        std::string text;
        graphics::GpuPlane background;
    };
}
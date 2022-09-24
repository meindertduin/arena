#pragma once

namespace ui {
    struct UICommand {
        virtual void execute() = 0;
    };

    struct ToggleOverlayCommand : public UICommand {
        void execute() override;
    };
}
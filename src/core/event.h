#pragma once

namespace core {
    struct Event {
        enum class EventType {
            ScreenResizeEvent,
            SettingChangeEvent,
        } event_type;
    };
}

#pragma once

namespace core {
    struct Event {
        enum class EventType {
            SettingChangeEvent,
            InputEvent,
        } event_type;
    };
}

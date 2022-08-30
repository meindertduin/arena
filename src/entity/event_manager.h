#pragma once

#include <unordered_map>
#include <typeinfo>
#include <stdexcept>

#include <functional>

#include "entity.h"

namespace entity {
    struct EventBase {
        Entity *entity = nullptr;
    };

    template<typename T>
    struct Event : public EventBase {
        inline static uint32_t _id;
    };

    // TODO remove for testing purposes
    struct PositionChangeEvent : public Event<PositionChangeEvent> {  };
    struct RotationChangeEvent : public Event<PositionChangeEvent> {  };

    struct TickEvent : public Event<TickEvent> {

    };

    using EventType = uint32_t;

    struct EventManager {
    public:
    template<typename T>
    static void register_event() {
        if (event_map.find(T::_id) != event_map.end()) {
            throw std::runtime_error("Eventtype already registered!");
        }

        event_map.insert({ T::_id, current_type++ });
    }

    private:
        static std::unordered_map<uint32_t, EventType> event_map;
        static EventType current_type;
    };
 
    inline std::unordered_map<uint32_t, EventType> EventManager::event_map;
    inline EventType EventManager::current_type = 0;

    inline static uint32_t next_event = 0;

    template<typename T>
    struct InitEvent {
        InitEvent() {
            T::_id = next_event++;
            EventManager::register_event<T>();
        }
    };

#define DECL_EVENT_HEADER(_c) \
    template<> uint32_t Event<_c>::_id; \
    struct __##_c##_init : InitEvent<_c> {}

#define DECL_EVENT_INIT(_c) \
    template struct Event<_c>; \
    template <> uint32_t Event<_c>::_id = 0; \
    static __##_c##_init _c##_initializer;

    DECL_EVENT_HEADER(TickEvent);
    DECL_EVENT_HEADER(PositionChangeEvent);
    DECL_EVENT_HEADER(RotationChangeEvent);
}

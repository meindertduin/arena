#pragma once

#include <unordered_map>
#include <typeinfo>
#include <stdexcept>

#include <functional>

#include "entity.h"
#include "../logging.h"

#include <glm/glm.hpp>
#include <glm/gtx/quaternion.hpp>

namespace entity {
    template<typename T>
    struct Event {
        inline static uint32_t _id;
        Entity *entity = nullptr;
        Event() = default;
        Event(Entity * entity) : entity(entity) { }
    };

    struct PositionChangeEvent : public Event<PositionChangeEvent> {
        PositionChangeEvent() = default;
        explicit PositionChangeEvent(Entity *entity) : Event<PositionChangeEvent>(entity) { }
    };
    struct RotationChangeEvent : public Event<RotationChangeEvent> { 
        glm::quat rotation;

        explicit RotationChangeEvent(glm::quat rotation) : rotation(rotation) {  }
        RotationChangeEvent(Entity *entity, glm::quat rotation) : Event<RotationChangeEvent>(entity), rotation(rotation) {  }
    };

    struct TickEvent : public Event<TickEvent> { };
    using EventType = uint32_t;

    class EventManager {
    public:
    template<typename T>
    static void register_event() {
        if (event_map.find(T::_id) != event_map.end()) {
            THROW_ERROR("Event of type %s already registered!", typeid(T).name());
        }

        event_map.insert({ T::_id, current_type++ });
    }

    private:
        static std::unordered_map<uint32_t, EventType> event_map;
        static EventType current_type;
    };
 
    inline std::unordered_map<uint32_t, EventType> EventManager::event_map;
    inline EventType EventManager::current_type = 0;

    inline uint32_t next_event = 0;

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

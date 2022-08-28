#pragma once

#include <unordered_map>
#include <typeinfo>
#include <stdexcept>

#include <functional>

namespace entity {
    struct EcsEventBase {
        int id;   
    };

    // TODO remove for testing purposes
    struct PositionChangeEvent : EcsEventBase {
        int x;
    };

    struct TickEvent : EcsEventBase {
    };

    using EventType = uint32_t;

    struct EventManager {
    public:

    template<typename T>
    static void register_event() {
        auto type_name = typeid(T).name();
        if (event_map.find(type_name) != event_map.end()) {
            throw std::runtime_error("Eventtype already registered!");
        }

        event_map.insert({ type_name, current_type++ });
    }

    template<typename T>
    static  EventType get_event_type() {
        auto type_name = typeid(T).name();

        if (event_map.find(type_name) == event_map.end()) {
            throw std::runtime_error("EventType is not registered");
        }

        return event_map[type_name];
    }

    private:
        static std::unordered_map<const char*, EventType> event_map;
        static EventType current_type;
    };
 
    inline std::unordered_map<const char*, EventType> EventManager::event_map;
    inline EventType EventManager::current_type = 0;
}

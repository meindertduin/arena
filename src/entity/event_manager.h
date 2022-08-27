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

    struct EventListener {
    public:
        void dispatch(EcsEventBase event) {
            for (auto &callback : callbacks) {
                callback(event);
            }   
        }
    private:
        // vector is not very fast
        std::vector<std::function<void(EcsEventBase)>> callbacks;
    };

    struct EventManager {
    public:
    template<typename T>
    void register_event() {
        auto event_name = typeid(T).name();
        if (event_listeners.find(event_name) != event_listeners.end()) {
            throw std::runtime_error("Registered event multiple times");
        }

        event_listeners.insert({ event_name, new EventListener() });
    }

    template<typename T>
    void dispatch_event(T event) {
        auto event_name = typeid(T).name();

        if (event_listeners.find(event_name) == event_listeners.end()) {
            throw std::runtime_error("Could not find listeners for event type");
        }
        // TODO dispatch should store the events in a queue so that after each tick/frame they can be handled all at once
        auto listener = event_listeners[event_name];
        listener->dispatch(event);
    }

    private:
        std::unordered_map<const char*, EventListener*> event_listeners;
    };
    
}

#pragma once

#include <functional>
#include <memory>
#include <list>

namespace core {
    template<typename T>
    struct EventHandler;

    template<typename T>
    class EventDispatcher {
    public:
        ~EventDispatcher() = default;
        EventDispatcher(const EventDispatcher&) = delete;
        EventDispatcher& operator=(const EventDispatcher&) = delete;
        EventDispatcher(EventDispatcher&&) = delete;
        EventDispatcher& operator=(EventDispatcher&&) = delete;

        void emit_event(const T &event);

        void add_event_handler(EventHandler<T> *eventHandler) {
            eventHandlers.push_back(eventHandler);
        }

        void remove_event_handler(EventHandler<T> *eventHandler) {
            eventHandlers.remove(eventHandler);
        }

        static EventDispatcher<T>* instance() {
            static EventDispatcher<T> dispatcher;
            return &dispatcher;
        }

    protected:
        EventDispatcher() = default;

    private:
        std::list<EventHandler<T>*> eventHandlers;
    };

    template<typename T>
    struct EventHandler {
    public:
        EventHandler(std::function<void(const T&)> &callback)
            : eventDispatcher(EventDispatcher<T>::instance()), callback(callback)
        {

        }

        ~EventHandler() {
            if (eventDispatcher)
                eventDispatcher->remove_event_handler(this);
        }

        EventHandler(const EventHandler&) = delete;
        EventHandler& operator=(const EventHandler&) = delete;
        EventHandler(EventHandler&&) = delete;
        EventHandler& operator=(EventHandler&&) = delete;

        void unlisten() {
            if (eventDispatcher) {
                eventDispatcher->removeEventHandler(this);
                eventDispatcher = nullptr;
            }
        }

        std::function<void(const T&)> callback;
    private:
        EventDispatcher<T> *eventDispatcher = nullptr;
    };

    template<typename T>
    void EventDispatcher<T>::emit_event(const T &event) {
        for (const auto eventHandler : eventHandlers) {
            eventHandler->callback(event);
        }
    }

    template<typename T>
    EventHandler<T> create_event_handler(std::function<void(const T &event)> callback) {
        auto eventHandler = EventHandler<T>(callback);
        EventDispatcher<T>::instance()->addEventHandler(eventHandler);

        return eventHandler;
    }

    template<typename T>
    std::unique_ptr<EventHandler<T>> create_unique_event_handler(std::function<void(const T &event)> callback) {
        auto event_handler = std::make_unique<EventHandler<T>>(callback);
        EventDispatcher<T>::instance()->add_event_handler(event_handler.get());

        return event_handler;
    }
}

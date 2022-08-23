#pragma once

#include <functional>
#include <memory>
#include <vector>

namespace core {
    template<typename T>
    struct EventHandler;

    template<typename T>
    class EventDispatcher {
    public:
        ~EventDispatcher() {

        }

        EventDispatcher(const EventDispatcher&) = delete;
        EventDispatcher& operator=(const EventDispatcher&) = delete;
        EventDispatcher(EventDispatcher&&) = delete;
        EventDispatcher& operator=(EventDispatcher&&) = delete;

        void emitEvent(const T &event);

        void addEventHandler(EventHandler<T> *eventHandler) {
            eventHandlers.push_back(eventHandler);
        }

        void removeEventHandler(EventHandler<T> *eventHandler) {
            // TODO IMPLEMENT
        }

        static EventDispatcher<T>* instance() {
            static EventDispatcher<T> dispatcher;
            return &dispatcher;
        }

    protected:
        EventDispatcher() = default;

    private:
        std::vector<EventHandler<T>*> eventHandlers;
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
                eventDispatcher->removeEventHandler(this);
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
    void EventDispatcher<T>::emitEvent(const T &event) {
        for (const auto eventHandler : eventHandlers) {
            eventHandler->callback(event);
        }
    }

    template<typename T>
    EventHandler<T> createEventHandler(std::function<void(const T &event)> callback) {
        auto eventHandler = EventHandler<T>(callback);
        EventDispatcher<T>::instance()->addEventHandler(eventHandler);

        return eventHandler;
    }

    template<typename T>
    std::unique_ptr<EventHandler<T>> createUniqueEventHandler(std::function<void(const T &event)> callback) {
        auto eventHandler = std::make_unique<EventHandler>(callback);
        EventDispatcher<T>::instance()->addEventHandler(eventHandler);

        return eventHandler;
    }
}

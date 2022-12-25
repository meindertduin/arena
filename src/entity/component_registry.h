#pragma once

#include "event_manager.h"

namespace entity {
    class IComponentArray;

    template<typename T>
    class ComponentArray;

    struct IComponentArrayStaticData {
        uint32_t id { 0 };
        virtual std::shared_ptr<IComponentArray> create_component_array() = 0;
    };

    template<typename T>
    struct ComponentArrayStaticData : public IComponentArrayStaticData {
        using EventHandlerFunction = std::function<void(T*, void*)>;
        using EventHandlersMap = std::unordered_map<EventType, EventHandlerFunction>;

        EventHandlersMap event_handlers = EventHandlersMap();

        template<typename E, typename F>
        void add_event_handler(F &&f) {
            auto handler = [f = std::forward<F>(f)](void *c, void *e) {
                ((reinterpret_cast<T*>(c)->*f)(*reinterpret_cast<const E*>(e)));
            };

            event_handlers[E::_id] = handler;
        }

        std::shared_ptr<IComponentArray> create_component_array() override {
            return std::make_shared<ComponentArray<T>>(this);
        }
    };

    class ComponentRegistry {
    public:
        using ComponentArrayStaticDataMap = std::unordered_map<uint32_t, std::shared_ptr<IComponentArrayStaticData>>;

        template<typename T>
        void register_component() {
            if (m_components_data.find(T::_id) != m_components_data.end()) {
                THROW_ERROR("Registered Component of m_type: %s more than once.", typeid(T).name());
            }

            auto component_data = std::make_shared<ComponentArrayStaticData<T>>();
            component_data->id = T::_id;

            m_components_data.insert({ T::_id, component_data });

            next_component_type++;
        }

        template<typename C, typename E, typename F>
        void add_event_handler(F && f) {
            get_static_component_data<C>()->template add_event_handler<E>(f);
        }

        ComponentArrayStaticDataMap& components_data() {
            return m_components_data;
        }

    private:
        uint32_t next_component_type { 0 };
        ComponentArrayStaticDataMap m_components_data;

        template<typename T>
        std::shared_ptr<ComponentArrayStaticData<T>> get_static_component_data() {
            if (m_components_data.find(T::_id) == m_components_data.end()) {
                THROW_ERROR("Could not find component of m_type: %s.", typeid(T).name());
            }

            return std::static_pointer_cast<ComponentArrayStaticData<T>>(m_components_data[T::_id]);
        }
    };
}
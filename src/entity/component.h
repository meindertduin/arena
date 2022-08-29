#pragma once 

#include "entity.h"
#include "component_array.h"
#include "ecs.h"

namespace entity {
    template<typename T>
    struct ComponentBase {
        uint32_t entity_id;

        inline static uint32_t _id;
        inline static ComponentArray<T>* _p;
    };

    inline static uint32_t next_component = 0;

    template<typename T>
    struct InitComponent {

        InitComponent() {
            T::_id = next_component++;
            Ecs::register_component<T>();

            init();
        }

        static void init();
    };

#define DECL_COMPONENT_HEADER(_c) \
    template<> uint32_t ComponentBase<_c>::_id; \
    template<> ComponentArray<_c>* ComponentBase<_c>::_p; \
    struct __##_c##_init : InitComponent<_c> {}

#define DECL_COMPONENT_INIT(_c) \
    template struct ComponentBase<_c>; \
    template <> uint32_t ComponentBase<_c>::_id = 0; \
    template <> ComponentArray<_c>* ComponentBase<_c>::_p = nullptr; \
    template <> void InitComponent<_c>::init()
}

#pragma once 

#include "entity.h"
#include "component_array.h"
#include "ecs.h"

namespace game {
    class Scene;
}

namespace entity {
    template<typename T>
    struct Component {
        Entity entity;
        game::Scene *scene;

        inline static uint32_t _id;
    };

    inline uint32_t next_component = 0;

    template<typename T>
    struct InitComponent {
        InitComponent() {
            if (next_component >= MaxComponents)
                THROW_ERROR("Max components of %s exceeded.", std::to_string(MaxComponents));

            T::_id = next_component;

            next_component += 1;
            Ecs::register_component<T>();

            init();
        }

        static void init();
    };

#define DECL_COMPONENT_HEADER(_c) \
    template<> uint32_t Component<_c>::_id; \
    struct __##_c##_init : InitComponent<_c> {}

#define DECL_COMPONENT_INIT(_c) \
    template struct Component<_c>; \
    template <> uint32_t Component<_c>::_id = 0; \
    __##_c##_init _c##__COUNTER__; \
    template <> void InitComponent<_c>::init()
}

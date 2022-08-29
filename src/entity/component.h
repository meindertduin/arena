#pragma once 

#include "entity.h"
#include "component_array.h"
#include "ecs.h"

namespace entity {
    template<typename T>
    struct ComponentBase {
        uint32_t entity_id;
        ComponentArray<T> *component_array;

        inline static uint32_t _id;
        inline static Ecs* _p;
    };

    template<typename T>
    struct InitComponent {
        InitComponent() {
            printf("hello world\n");
        }
    };

#define DECL_COMPONENT_HADER(_c) \
    template<> uint32_t ComponentBase<_c>::_id; \
    template<> Ecs* ComponentBase<_c>::_p; \
    struct __##_c##_init : InitComponent<_c> {}
}

#define DECL_COMPONENT_INIT(_c) \
    template struct ComponentBase<_c>; \
    template <> uint32_t ComponentBase<_c>::_id = __COUNTER__; \
    template <> Ecs* ComponentBase<_c>::_p = nullptr; \
    static __##_c##_init _c##_initializer;

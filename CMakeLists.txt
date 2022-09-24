cmake_minimum_required(VERSION 3.18)
project(arena)

set(CMAKE_CXX_STANDARD 20)
set(arena_version 0.1)

set(PROJECT_VERSION ${arena_version})
project(${PROJECT_NAME} VERSION ${arena_version} LANGUAGES CXX C)

set(SOURCES
        src/main.cpp
        src/core/window.cpp
        src/core/linear_allocator.h src/core/linear_allocator.cpp
        src/graphics/mesh.cpp
        src/graphics/terrain.cpp
        src/graphics/renderer.cpp
        src/graphics/texture.cpp
        src/graphics/gpu_buffer.cpp
        src/graphics/shader.cpp
        src/graphics/render_target.cpp
        src/graphics/skybox.h src/graphics/skybox.cpp
        external/glad/glad.c
        src/entity/event_manager.cpp
        src/entity/entity.cpp
        src/entity/ec_component_inits.cpp
        src/entity/ec_transform.cpp
        src/entity/ec_collision_box.cpp
        src/entity/ec_physics.h
        src/entity/ec_first_person_camera.cpp
        src/entity/ec_command.cpp
        src/entity/ec_player.cpp
        src/entity/static_render_system.cpp
        src/entity/terrain_collision_system.cpp
        src/entity/ec_static_mesh.cpp
        src/game/game_state.cpp
        src/game/map.cpp
        src/input/input.cpp
        src/input/input_manager.cpp
        src/assets/obj_loader.cpp
        src/assets/cache.cpp
        src/assets/terrain_loader.cpp
        src/assets/file_reader.cpp
        src/physics/physics_system.h
        src/physics/physics_system.cpp
        src/core/allocator.h
        src/core/stack_allocator.cpp
        src/core/stack_allocator.h
        src/core/list_allocator.cpp
        src/core/list_allocator.h
        src/core/singly_linked_list.h src/core/program_time.cpp src/core/program_time.h src/graphics/font.h src/graphics/font.cpp src/graphics/geometry.h src/graphics/geometry.cpp src/input/key_bindings.h src/entity/ec_control.h src/entity/movement_system.cpp src/entity/movement_system.h)

set(HEADERS include)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -fno-omit-frame-pointer -D__extern_always_inline=inline -D_XOPEN_SOURCE_EXTENDED")

add_executable(${PROJECT_NAME} ${SOURCES})
target_include_directories(
    ${PROJECT_NAME} PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/external
    ${PROJECT_NAME} PUBLIC
    /usr/include/freetype2
)
target_link_libraries(${PROJECT_NAME} glfw GL dl freetype)

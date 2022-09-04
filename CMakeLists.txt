cmake_minimum_required(VERSION 3.18)
project(arena)

set(CMAKE_CXX_STANDARD 20)
set(arena_version 0.1)

set(PROJECT_VERSION ${arena_version})
project(${PROJECT_NAME} VERSION ${arena_version} LANGUAGES CXX C)

set(SOURCES
    src/main.cpp
    src/core/window.cpp
    src/graphics/mesh.cpp
    src/graphics/renderer.cpp
    src/graphics/texture.cpp
    src/graphics/gpu_buffer.cpp
    src/graphics/shader.cpp
    src/graphics/render_target.cpp
    external/glad/glad.c
    src/entity/event_manager.cpp
    src/entity/entity.cpp
    src/entity/ec_transform.cpp
    src/entity/ec_first_person_camera.cpp
    src/entity/ec_command.cpp
    src/entity/ec_player.cpp
    src/entity/game_state.cpp
    src/entity/static_render_system.cpp
    src/entity/ec_static_mesh.cpp
    src/input/input.cpp
    src/input/input_manager.cpp
    src/assets/obj_loader.cpp
    src/assets/cache.cpp
)

set(HEADERS include)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -fno-omit-frame-pointer -D__extern_always_inline=inline -D_XOPEN_SOURCE_EXTENDED")

add_executable(${PROJECT_NAME} ${SOURCES})
target_include_directories(
    ${PROJECT_NAME} PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/external
    ${PROJECT_NAME} PUBLIC
)
target_link_libraries(${PROJECT_NAME} glfw GL dl)

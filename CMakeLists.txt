cmake_minimum_required(VERSION 3.18)
project(arena)

set(CMAKE_CXX_STANDARD 20)
set(arena_version 0.1)

set(PROJECT_VERSION ${arena_version})
project(${PROJECT_NAME} VERSION ${arena_version} LANGUAGES CXX C)

set(SOURCES
        src/main.cpp
        external/glad/glad.c
        src/entity/systems_collection.cpp src/entity/systems_collection.h)

include(${CMAKE_CURRENT_SOURCE_DIR}/src/assets/CMakeLists.txt)
include(${CMAKE_CURRENT_SOURCE_DIR}/src/core/CMakeLists.txt)
include(${CMAKE_CURRENT_SOURCE_DIR}/src/entity/CMakeLists.txt)
include(${CMAKE_CURRENT_SOURCE_DIR}/src/game/CMakeLists.txt)
include(${CMAKE_CURRENT_SOURCE_DIR}/src/graphics/CMakeLists.txt)
include(${CMAKE_CURRENT_SOURCE_DIR}/src/input/CMakeLists.txt)
include(${CMAKE_CURRENT_SOURCE_DIR}/src/physics/CMakeLists.txt)
include(${CMAKE_CURRENT_SOURCE_DIR}/src/ui/CMakeLists.txt)

set(HEADERS include)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -fno-omit-frame-pointer -D__extern_always_inline=inline -D_XOPEN_SOURCE_EXTENDED")

add_executable(${PROJECT_NAME} ${SOURCES} ${ASSETS_SOURCES} ${CORE_SOURCES} ${ENTITY_SOURCES} ${GAME_SOURCES} ${GRAPHICS_SOURCES} ${INPUT_SOURCES} ${PHYSICS_SOURCES} ${UI_SOURCES})
target_include_directories(
    ${PROJECT_NAME} PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/external
    ${PROJECT_NAME} PUBLIC
    /usr/include/freetype2
)
target_link_libraries(${PROJECT_NAME} glfw GL dl freetype)

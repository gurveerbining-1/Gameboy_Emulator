cmake_minimum_required(VERSION 3.10)

project(gb_emulator LANGUAGES CXX)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Output folders
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)

# Source files
file(GLOB_RECURSE SOURCES CONFIGURE_DEPENDS
    bus/*.cpp
    cartridge/*.cpp
    CPU/*.cpp
    platform/*.cpp
)

add_executable(gb_emulator ${SOURCES})

target_include_directories(gb_emulator PRIVATE include)
target_include_directories(gb_emulator PRIVATE include)

# ---- SDL2 ----
find_package(SDL2 REQUIRED)

target_link_libraries(gb_emulator PRIVATE SDL2::SDL2)

# ============================
# CPU Tests
# ============================

file(GLOB_RECURSE TEST_SOURCES CONFIGURE_DEPENDS
    tests/*.cpp
    bus/*.cpp
    cartridge/*.cpp
    CPU/*.cpp 
)

add_executable(cpu_tests 
    ${TEST_SOURCES}
)

target_include_directories(cpu_tests PRIVATE include)
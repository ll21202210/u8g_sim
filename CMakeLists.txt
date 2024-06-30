cmake_minimum_required(VERSION 3.10)
project(u8g2)
set(CMAKE_C_STANDARD 11)#C11
set(CMAKE_CXX_STANDARD 17)#C17
set(CMAKE_CXX_STANDARD_REQUIRED ON)

INCLUDE_DIRECTORIES(${PROJECT_SOURCE_DIR})

file(GLOB_RECURSE INCLUDES "u8g2/*.h" )
file(GLOB_RECURSE SOURCES  "u8g2/*.c"  "main.c" "Menu/*.c")

include_directories("u8g2/" "sdl/i686-w64-mingw32/include/SDL2/" "Menu/")

add_compile_definitions("unix")

if(CMAKE_SIZEOF_VOID_P EQUAL 4)
    set(sdl2_config_path "${CMAKE_CURRENT_LIST_DIR}/sdl/i686-w64-mingw32/lib/cmake/SDL2/sdl2-config.cmake")
elseif(CMAKE_SIZEOF_VOID_P EQUAL 8)
    set(sdl2_config_path "${CMAKE_CURRENT_LIST_DIR}/sdl/x86_64-w64-mingw32/lib/cmake/SDL2/sdl2-config.cmake")
else()
    set(SDL2_FOUND FALSE)
    return()
endif()

if(NOT EXISTS "${sdl2_config_path}")
    message(WARNING "${sdl2_config_path} does not exist: MinGW development package is corrupted")
    set(SDL2_FOUND FALSE)
    return()
endif()

include("${sdl2_config_path}")


SET(EXECUTABLE_OUTPUT_PATH ${PROJECT_SOURCE_DIR}/bin)
SET(CMAKE_CXX_FLAGS "-O3")

find_package(SDL2 REQUIRED SDL2)
include_directories(${SDL2_INCLUDE_DIRS})
add_executable(main main.c  ${SOURCES} ${INCLUDES})

target_link_libraries(main PRIVATE SDL2 )
add_custom_target (run COMMAND ${EXECUTABLE_OUTPUT_PATH}/main)

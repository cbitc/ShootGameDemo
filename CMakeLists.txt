cmake_minimum_required(VERSION 3.15)
project(MyGame)
set(CMAKE_CXX_STANDARD 17)

set(EXECUTABLE_OUTPUT_PATH ${CMAKE_CURRENT_SOURCE_DIR}/bin)
file(GLOB SRC CMAKE_CONFIGURE_DEPENDS ${CMAKE_CURRENT_SOURCE_DIR}/src/*.cpp)

add_executable(main ${SRC})

include_directories(
    ${CMAKE_CURRENT_SOURCE_DIR}/SDL2/include
    ${CMAKE_CURRENT_SOURCE_DIR}/include
    ${CMAKE_CURRENT_SOURCE_DIR}/ECS/include)

target_link_directories(main PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/SDL2/lib/)

target_link_libraries(main PUBLIC libSDL2.dll.a)

target_link_libraries(main PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/SDL2/lib/libSDL2_image.dll.a)


cmake_minimum_required(VERSION 3.11)
project(pacmanf1n LANGUAGES CXX)

set(SFML_STATIC_LIBRARIES TRUE)
set(CMAKE_EXE_LINKER_FLAGS "-static -static-libgcc")
option(BUILD_SHARED_LIBS ON)

find_package(OpenGL REQUIRED)

add_subdirectory(${PROJECT_SOURCE_DIR}/lib/SFML-2.5.1)

add_executable(pacmanf1n main.cpp Ghost.cpp Ghost.h Pacman.cpp Pacman.h Place.cpp Place.h game.cpp game.h)
target_link_libraries(pacmanf1n PRIVATE sfml-audio sfml-graphics sfml-window sfml-system ${OPENGL_LIBRARIES})

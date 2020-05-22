cmake_minimum_required(VERSION 3.10)

project(Boids VERSION 0.0)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED True)

set(SFML_INCLUDE_DIR "./SFML/include")
set(SFML_LIBRARY_DIR "./SFML/build/lib")

#link_directories(SFML_LIBRARY_DIR)
include_directories(SFML_INCLUDE_DIR)

find_package(SFML 2.5.1 COMPONENTS system window graphics)

add_executable(main main.cpp boid.cpp predator.cpp prey.cpp system.cpp flock.cpp vec2.hpp)
target_link_libraries(main sfml-graphics sfml-window sfml-system)

add_compile_options(-Wall -Wextra -pedantic -Werror)

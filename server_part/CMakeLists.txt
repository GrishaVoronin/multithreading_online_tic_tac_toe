cmake_minimum_required(VERSION 3.28)
project(server_part)

set(CMAKE_CXX_STANDARD 20)

add_executable(server_part main.cpp
        Game/Field/Field.hpp
        Game/Field/Field.cpp
        Game/Game.hpp
        Game/Game.cpp)

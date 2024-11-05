cmake_minimum_required(VERSION 3.28)
project(server)

set(CMAKE_CXX_STANDARD 20)

add_executable(server main.cpp
        Game/Field/Field.hpp
        Game/Field/Field.cpp
        Game/Game.hpp
        Game/Game.cpp
        Connector/Connector.hpp
        Connector/Connector.cpp
        Server.hpp
        Server.cpp)

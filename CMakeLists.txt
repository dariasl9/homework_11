cmake_minimum_required(VERSION 3.15)
project(join_server)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(Boost REQUIRED COMPONENTS system)

add_executable(join_server
    main.cpp
    database/database.cpp
    database/database_manager.cpp
    protocol/command_parser.cpp
    protocol/command_handler.cpp
    network/session.cpp
    server.cpp
)

target_include_directories(join_server PRIVATE
    database
    protocol
    network
)

target_link_libraries(join_server PRIVATE Boost::system)

install(TARGETS join_server DESTINATION bin)
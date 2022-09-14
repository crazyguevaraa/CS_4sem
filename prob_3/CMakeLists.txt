cmake_minimum_required(VERSION 3.8)

include_directories(/usr/local/include)
include_directories(.)
include_directories(srl_core)
include_directories(clc_core)
include_directories(server/core)
include_directories(client/core)

link_directories(/usr/local/lib)

add_compile_options("-g")

add_subdirectory(srl_core)
add_subdirectory(clc_core)
add_subdirectory(server)
add_subdirectory(client)
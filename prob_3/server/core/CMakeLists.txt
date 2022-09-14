cmake_minimum_required(VERSION 3.8)

add_library(core STATIC
  common_server_core.c
  datagram_server_core.c
  stream_server_core.c
)

target_link_libraries(core
  srl_core
  clc_core
  pthread
)
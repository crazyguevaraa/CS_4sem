cmake_minimum_required(VERSION 3.8)

add_library(core STATIC
  common_client_core.c
  stream_client_core.c
  datagram_client_core.c
)

target_link_libraries(core
  srl_core
  clc_core
)
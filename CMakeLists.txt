cmake_minimum_required(VERSION 3.5)

if(NOT CMAKE_BUILD_TYPE AND NOT CMAKE_CONFIGURATION_TYPES)
  message("Setting build type to 'Debug' as none was specified.")
  set(CMAKE_BUILD_TYPE Debug CACHE STRING "Choose the type of build." FORCE)
  set_property(CACHE CMAKE_BUILD_TYPE PROPERTY STRINGS "Debug" "Release" "MinSizeRel" "RelWithDebInfo")
endif()

if(NOT CMAKE_CXX_FLAGS)
  set(CMAKE_CXX_FLAGS "-std=c++11" CACHE STRING "Choose the type of build." FORCE)
  message("Setting build type to '"${CMAKE_CXX_FLAGS}"' as none was specified.")
endif()

project(main)

include_directories(
    ${CMAKE_CURRENT_SOURCE_DIR}/libs
)

link_directories(
    ${CMAKE_CURRENT_SOURCE_DIR}/libs/base/build
    ${CMAKE_CURRENT_SOURCE_DIR}/libs/pcap/build
)

add_executable(main main.cpp)

target_link_libraries(main
  PUBLIC
    pcap net_base)
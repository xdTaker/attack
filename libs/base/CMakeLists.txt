cmake_minimum_required(VERSION 3.5)

SET(CMAKE_CXX_COMPILER "/usr/bin/g++")

if(NOT CMAKE_BUILD_TYPE AND NOT CMAKE_CONFIGURATION_TYPES)
  #在命令行中输出message里的信息
  message("Setting build type to 'Debug' as none was specified.")
  #不管CACHE里有没有设置过CMAKE_BUILD_TYPE这个变量，都强制赋值这个值为RelWithDebInfo
  set(CMAKE_BUILD_TYPE Debug CACHE STRING "Choose the type of build." FORCE)

  # 当使用cmake-gui的时候，设置构建级别的四个可选项
  set_property(CACHE CMAKE_BUILD_TYPE PROPERTY STRINGS "Debug" "Release"
    "MinSizeRel" "RelWithDebInfo")
endif()

if(NOT CMAKE_CXX_FLAGS)
  set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11" CACHE STRING "Choose the type of build." FORCE)
  message("Setting build type to '"${CMAKE_CXX_FLAGS}"' as none was specified.")
endif()


project(net_base)

include_directories(
    ${CMAKE_CURRENT_SOURCE_DIR}/..
)

add_library(net_base SHARED
    ${CMAKE_CURRENT_SOURCE_DIR}/link/eth.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/net/vlan.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/net/net-layer.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/net/ip.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/trans/trans-layer.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/trans/tcp.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/common.cpp
)

add_library(net_base_static STATIC
    ${CMAKE_CURRENT_SOURCE_DIR}/link/eth.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/net/vlan.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/net/net-layer.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/net/ip.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/trans/trans-layer.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/trans/tcp.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/common.cpp
)
SET_TARGET_PROPERTIES(net_base_static PROPERTIES OUTPUT_NAME "net_base")

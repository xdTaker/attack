cmake_minimum_required(VERSION 3.5)

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
  set(CMAKE_CXX_FLAGS "-std=c++11" CACHE STRING "Choose the type of build." FORCE)
  message("Setting build type to '"${CMAKE_CXX_FLAGS}"' as none was specified.")
endif()


project(pcap)

link_directories(
    ${CMAKE_CURRENT_SOURCE_DIR}/../base/build
    ${CMAKE_CURRENT_SOURCE_DIR}/build
)

include_directories(
    ${CMAKE_CURRENT_SOURCE_DIR}/../
)
find_library(NET_BASE_STATIC libnet_base.a)

add_library(pcap SHARED
    ${CMAKE_CURRENT_SOURCE_DIR}/pcap.cpp
)

add_library(pcap_static STATIC
    ${CMAKE_CURRENT_SOURCE_DIR}/pcap.cpp
)
SET_TARGET_PROPERTIES(pcap_static PROPERTIES OUTPUT_NAME "pcap")

target_link_libraries(pcap net_base)
target_link_libraries(pcap_static NET_BASE_STATIC)

project(pcaptool)

add_executable(pcaptool pcap-tools.cpp)

target_link_libraries(pcaptool
  PUBLIC
    pcap net_base)

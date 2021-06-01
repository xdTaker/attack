cmake_minimum_required(VERSION 3.5)

# SET(CMAKE_CXX_COMPILER "/usr/bin/g++")

if(NOT CMAKE_BUILD_TYPE AND NOT CMAKE_CONFIGURATION_TYPES)
  message("Setting build type to 'Debug' as none was specified.")
  set(CMAKE_BUILD_TYPE Debug CACHE STRING "Choose the type of build." FORCE)
  # 当使用cmake-gui的时候，设置构建级别的四个可选项
  set_property(CACHE CMAKE_BUILD_TYPE PROPERTY STRINGS "Debug" "Release"
    "MinSizeRel" "RelWithDebInfo")
endif()

set(CMAKE_CXX_FLAGS
    -std=c++11
)

if(NOT CMAKE_INSTALL_PREFIX)
  set(CMAKE_INSTALL_PREFIX "/usr/local")
endif()

set(ROOT_DIR ${CMAKE_CURRENT_SOURCE_DIR}/../..)
set(CMAKE_INSTALL_INCLUDEDIR ${CMAKE_INSTALL_PREFIX}/include)
set(PROTO_VERSION 1.0)
set(PROTO_SOVERSION 1)

project(proto)

# 资源
include_directories(
    ${CMAKE_CURRENT_SOURCE_DIR}/..
)
set(SRC_LIST
    ${CMAKE_CURRENT_SOURCE_DIR}/link/eth.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/link/vlan.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/net/net-layer.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/net/ip.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/trans/trans-layer.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/trans/tcp.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/trans/udp.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/proto.cpp
)

# 动态库
add_library(proto SHARED ${SRC_LIST})
set_target_properties(proto
    PROPERTIES
        LIBRARY_OUTPUT_DIRECTORY ${ROOT_DIR}/target
        VERSION ${PROTO_VERSION}
        SOVERSION ${PROTO_SOVERSION}
)

# 静态库
add_library(proto_static STATIC ${SRC_LIST})
set_target_properties(proto_static
    PROPERTIES
        OUTPUT_NAME "proto"
        ARCHIVE_OUTPUT_DIRECTORY ${ROOT_DIR}/target
)

# install
install(TARGETS proto proto_static
    LIBRARY DESTINATION ${CMAKE_INSTALL_PREFIX}/lib
    ARCHIVE DESTINATION ${CMAKE_INSTALL_PREFIX}/lib
)
install(DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}
    DESTINATION ${CMAKE_INSTALL_PREFIX}/include
    PATTERN "*.cpp" EXCLUDE
    PATTERN "*.txt" EXCLUDE
)
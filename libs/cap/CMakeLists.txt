cmake_minimum_required(VERSION 3.5)

if(NOT CMAKE_BUILD_TYPE AND NOT CMAKE_CONFIGURATION_TYPES)
  set(CMAKE_BUILD_TYPE Debug CACHE STRING "Choose the type of build." FORCE)
endif()

set(CMAKE_CXX_FLAGS
    -std=c++11
)

if(NOT CMAKE_INSTALL_PREFIX)
  set(CMAKE_INSTALL_PREFIX "/usr/local")
endif()

set(ROOT_DIR ${CMAKE_CURRENT_SOURCE_DIR}/../..)
set(PCAP_VERSION 1.0)
set(PCAP_SOVERSION 1)

project(cap)

include_directories(
    ${CMAKE_CURRENT_SOURCE_DIR}/../
)

link_directories(
    CMAKE_INSTALL_PREFIX/lib
    /usr/local/lib
)

# 动态库
add_library(cap SHARED
    ${CMAKE_CURRENT_SOURCE_DIR}/cap.cpp
)
target_link_libraries(cap proto)
set_target_properties(cap
    PROPERTIES
        LIBRARY_OUTPUT_DIRECTORY ${ROOT_DIR}/target
        VERSION ${PCAP_VERSION}
        SOVERSION ${PCAP_SOVERSION}
)

# 静态库
add_library(cap_static STATIC
    ${CMAKE_CURRENT_SOURCE_DIR}/cap.cpp
)
find_library(PROTO_STATIC libproto.a)
target_link_libraries(cap_static PROTO_STATIC)
set_target_properties(cap_static
    PROPERTIES
        OUTPUT_NAME "cap"
        ARCHIVE_OUTPUT_DIRECTORY ${ROOT_DIR}/target
)

# bin
project(captool)

add_executable(captool ${CMAKE_CURRENT_SOURCE_DIR}/cap-tools.cpp)

target_link_libraries(captool
  PUBLIC
    cap proto base
)
set_target_properties(captool
    PROPERTIES
        RUNTIME_OUTPUT_DIRECTORY ${ROOT_DIR}/target
        INSTALL_RPATH_USE_LINK_PATH TRUE
)

# install
install(TARGETS cap cap_static captool
    LIBRARY DESTINATION ${CMAKE_INSTALL_PREFIX}/lib
    ARCHIVE DESTINATION ${CMAKE_INSTALL_PREFIX}/lib
    RUNTIME DESTINATION ${CMAKE_INSTALL_PREFIX}/bin
)
install(DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}
    DESTINATION ${CMAKE_INSTALL_PREFIX}/include
    PATTERN "*.cpp" EXCLUDE
    PATTERN "*.txt" EXCLUDE
)
cmake_minimum_required(VERSION 3.5)

project(base)

# SET(CMAKE_CXX_COMPILER "/usr/bin/g++")

add_compile_options(-W -Wall)
if(CMAKE_COMPILER_IS_GNUCXX)    # gcc编译器
    add_compile_options(-std=c++11)
endif()

set(ROOT_DIR ${CMAKE_CURRENT_SOURCE_DIR}/../..)
set(BASE_VERSION 1.0)
set(BASE_SOVERSION 1)

if(NOT CMAKE_INSTALL_PREFIX)
  set(CMAKE_INSTALL_PREFIX "/usr/local")
endif()
set(CMAKE_INSTALL_INCLUDEDIR ${CMAKE_INSTALL_PREFIX}/include)

# 资源
include_directories(
    ${CMAKE_CURRENT_SOURCE_DIR}/..
)
set(SRC_LIST
    ${CMAKE_CURRENT_SOURCE_DIR}/encode.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/file-kit.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/str-kit.cpp
)

# 动态库
add_library(base SHARED ${SRC_LIST})
set_target_properties(base
    PROPERTIES
        LIBRARY_OUTPUT_DIRECTORY ${ROOT_DIR}/target
        VERSION ${BASE_VERSION}
        SOVERSION ${BASE_SOVERSION}
)

# 静态库
add_library(base_static STATIC ${SRC_LIST})
set_target_properties(base_static
    PROPERTIES
        OUTPUT_NAME "base"
        ARCHIVE_OUTPUT_DIRECTORY ${ROOT_DIR}/target
)

# install
install(TARGETS base base_static
    LIBRARY DESTINATION ${CMAKE_INSTALL_PREFIX}/lib
    ARCHIVE DESTINATION ${CMAKE_INSTALL_PREFIX}/lib
)
install(DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}
    DESTINATION ${CMAKE_INSTALL_PREFIX}/include
    PATTERN "*.cpp" EXCLUDE
    PATTERN "*.txt" EXCLUDE
)
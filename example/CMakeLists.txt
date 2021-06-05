cmake_minimum_required(VERSION 3.5)

if(NOT CMAKE_BUILD_TYPE AND NOT CMAKE_CONFIGURATION_TYPES)
  set(CMAKE_BUILD_TYPE Debug CACHE STRING "Choose the type of build." FORCE)
endif()

add_compile_options(-W -Wall)
if(CMAKE_COMPILER_IS_GNUCXX)    # gcc编译器
    add_compile_options(-std=c++11)
endif()

set(ROOT_DIR ${CMAKE_CURRENT_SOURCE_DIR}/..)

project(example)

include_directories(
    /usr/local/include
)

link_directories(
    /usr/local/lib
)

add_executable(example ${CMAKE_CURRENT_SOURCE_DIR}/test.cpp)

set_target_properties(example
    PROPERTIES
        RUNTIME_OUTPUT_DIRECTORY ${ROOT_DIR}/target
)

target_link_libraries(example
PUBLIC
    cap proto base
)

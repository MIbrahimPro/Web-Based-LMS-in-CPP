cmake_minimum_required(VERSION 3.15)
project(LMS_Server LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(LIB_DIR "${CMAKE_CURRENT_SOURCE_DIR}/libraries")
set(HTTPLIB_PATH "${LIB_DIR}/httplib.h")

if(NOT EXISTS ${HTTPLIB_PATH})
    message(STATUS "httplib.h not found. Downloading from GitHub...")
    file(MAKE_DIRECTORY ${LIB_DIR})
    file(DOWNLOAD
        "https://raw.githubusercontent.com/yhirose/cpp-httplib/master/httplib.h"
        ${HTTPLIB_PATH}
        SHOW_PROGRESS
    )
endif()

include_directories(include libraries)

file(GLOB SHARED_SRC "src/*.cpp")

add_executable(lms_server main.cpp ${SHARED_SRC})

add_executable(seeder seeder.cpp ${SHARED_SRC})

if(WIN32)
    target_link_libraries(lms_server ws2_32)
    target_link_libraries(seeder ws2_32)
endif()

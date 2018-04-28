cmake_minimum_required(VERSION 3.1)
project(bloody)

find_package(PkgConfig REQUIRED)
pkg_search_module(LIBUSB1 REQUIRED libusb-1.0)
include_directories(SYSTEM ${LIBUSB1_INCLUDE_DIRS})

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

set(SOURCE_FILES
    main.cpp)

add_executable(bloody ${SOURCE_FILES} Mouse.cpp Mouse.h)
target_link_libraries(bloody ${LIBUSB1_LIBRARIES})

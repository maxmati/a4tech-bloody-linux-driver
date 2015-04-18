cmake_minimum_required(VERSION 3.1)
project(bloody)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11 -I/usr/include/libusb-1.0  -lusb-1.0") #TODO: findlibusb

set(SOURCE_FILES
    main.cpp)

add_executable(bloody ${SOURCE_FILES} Mouse.cpp Mouse.h)
cmake_minimum_required(VERSION 3.5)

project(rcg LANGUAGES CXX)

find_package(OpenCV REQUIRED)
include_directories(${OpenCV_INCLUDE_DIRS})

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_executable(rcg main.cpp)

install(TARGETS rcg
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR})

target_link_libraries(rcg ${OpenCV_LIBS})

cmake_minimum_required(VERSION 3.27)
project(Mandelbrot VERSION 0.1.0 LANGUAGES C CXX)

include(CTest)
enable_testing()

set(
    CPP_SOURCE_FILES
    src/Main.cpp
)

set(
    CPP_HEADER_FILES
)

add_executable(${PROJECT_NAME} ${CPP_SOURCE_FILES} ${CPP_HEADER_FILES})

set(CPACK_PROJECT_NAME ${PROJECT_NAME})
set(CPACK_PROJECT_VERSION ${PROJECT_VERSION})
include(CPack)
cmake_minimum_required(VERSION 3.27)
project(Mandelbrot VERSION 0.1.0 LANGUAGES C CXX)

include(CTest)
enable_testing()

set(
    CPP_SOURCE_FILES
    src/Main.cpp
    src/ReadFile.cpp
    src/ErrorHandling.cpp
)

set(
    CPP_HEADER_FILES
    src/ReadFile.h
    src/ErrorHandling.h
)

add_executable(${PROJECT_NAME} ${CPP_SOURCE_FILES} ${CPP_HEADER_FILES})

add_subdirectory(dependencies/glfw)
add_subdirectory(dependencies/glew)

target_include_directories(
    ${PROJECT_NAME}
    PUBLIC dependencies/glfw/include
    PUBLIC dependencies/glew/include
)

target_link_libraries(
    ${PROJECT_NAME}
    opengl32 glfw libglew_static
)

add_compile_definitions(GLEW_STATIC)

set(CPACK_PROJECT_NAME ${PROJECT_NAME})
set(CPACK_PROJECT_VERSION ${PROJECT_VERSION})
include(CPack)
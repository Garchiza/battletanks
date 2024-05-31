cmake_minimum_required(VERSION 3.29 FATAL_ERROR)

set(PR_NAME battletanks)
project(${PR_NAME})

add_executable(${PR_NAME} src/main.cpp)

set (GLFW_BUILD_DOCS OFF CACHE BOOL "" FORCE)
set (GLFW_BUILD_TESTS OFF CACHE BOOL "" FORCE)
set (GLFW_BUILD_EXAMPLES OFF CACHE BOOL "" FORCE)
set (GLFW_INSTALL OFF CACHE BOOL "" FORCE)

add_subdirectory(external/glfw)
target_link_libraries(${PR_NAME} glfw)
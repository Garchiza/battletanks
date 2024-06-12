cmake_minimum_required(VERSION 3.29 FATAL_ERROR)

set(PR_NAME battletanks)
project(${PR_NAME})

add_executable(${PR_NAME}
src/main.cpp
src/Renderer/ShaderProgramm.cpp
src/Renderer/ShaderProgramm.h
src/Resources/ResourceManager.cpp
src/Resources/ResourceManager.h)

target_compile_features(${PR_NAME} PUBLIC cxx_std_23)

set (GLFW_BUILD_DOCS OFF CACHE BOOL "" FORCE)
set (GLFW_BUILD_TESTS OFF CACHE BOOL "" FORCE)
set (GLFW_BUILD_EXAMPLES OFF CACHE BOOL "" FORCE)
set (GLFW_INSTALL OFF CACHE BOOL "" FORCE)

add_subdirectory(external/glfw)
target_link_libraries(${PR_NAME} glfw)

add_subdirectory(external/glad)
target_link_libraries(${PR_NAME} glad)

set_target_properties(${PR_NAME} PROPERTIES RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin/)

add_custom_command(TARGET ${PR_NAME} POST_BUILD
COMMAND ${CMAKE_COMMAND} -E copy_directory
${CMAKE_SOURCE_DIR}/res $<TARGET_FILE_DIR:${PR_NAME}>/res)
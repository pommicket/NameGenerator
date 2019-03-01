cmake_minimum_required(VERSION 2.8)
project(namegenerator_client C)

set(CMAKE_BUILD_TYPE Release)
set(CMAKE_C_FLAGS "-Wall -std=c89")

set(src main.c)

add_subdirectory(namegenerator)

add_executable(namegenerator_client ${src})
target_link_libraries(${PROJECT_NAME} namegenerator)
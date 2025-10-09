# ------ Set the basic options for the demo project ------- #
message(STATUS "# Set the basic options for the external demo project")

cmake_minimum_required(VERSION 3.20)
project(ExtDemofile LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# ------ Create the executable program ------ #
if (WIN32)
    message(STATUS "Demo Platform : Windows")
    add_executable(${PROJECT_NAME} WIN32)
else()
    message(STATUS "Demo Platform : Others")
    add_executable(${PROJECT_NAME})
endif()

# ------ Load the log project ------ #
include(${CMAKE_SOURCE_DIR}/cmake/ExternalProject.cmake)

add_external_library(
    PROJECT_NAME LogProject_Ext
    LIBRARY_NAME LogProject
    GIT_REPOSITORY https://github.com/Winteradio/Log.git
    GIT_TAG CMAKE_TEST
)

# ------ Set the properties the executable program ------ #
target_sources(${PROJECT_NAME} PRIVATE
    ${CMAKE_CURRENT_SOURCE_DIR}/main.cpp
)
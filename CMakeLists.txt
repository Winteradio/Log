set(PROJECT_NAME LogProject)

if (TARGET ${PROJECT_NAME})
    message(STATUS "# ${PROJECT_NAME} is already defined. Skipping build configuration.")
    
    return()
endif()

cmake_minimum_required(VERSION 3.20)
project(${PROJECT_NAME} LANGUAGES CXX)

# ------ Create the library ------- #
include(${CMAKE_SOURCE_DIR}/external/CMake/Library.cmake)

set(LIBRARY_TYPE "SHARED" CACHE STRING "Build a shared library instead of a static one")

set(MAIN_DIR ${CMAKE_CURRENT_SOURCE_DIR})
set(HEADER_DIR ${MAIN_DIR}/include)
set(SOURCE_DIR ${MAIN_DIR}/src)

set(INCLUDE_DIR_LIST
    ${MAIN_DIR}/include
)

set(HEADER_LIST
    ${HEADER_DIR}/Log.h
    ${HEADER_DIR}/LogConstants.h
    ${HEADER_DIR}/LogDefaultHandler.h
    ${HEADER_DIR}/LogHandler.h
    ${HEADER_DIR}/LogMessage.h
    ${HEADER_DIR}/LogManager.h
    ${HEADER_DIR}/LogPlatform.h
    ${HEADER_DIR}/LogUtils.h
)

set(SOURCE_LIST
    ${SOURCE_DIR}/Log.cpp
    ${SOURCE_DIR}/LogHandler.cpp
    ${SOURCE_DIR}/LogDefaultHandler.cpp
    ${SOURCE_DIR}/LogManager.cpp
    ${SOURCE_DIR}/LogMessage.cpp
    ${SOURCE_DIR}/LogUtils.cpp
)

create_library(
    LIBRARY_TYPE ${LIBRARY_TYPE}
    TARGET_NAME ${PROJECT_NAME}
    PUBLIC_HEADERS ${HEADER_LIST}
    PRIVATE_SOURCES ${SOURCE_LIST}
)

install_library(
    TARGET_NAME ${PROJECT_NAME}
    INCLUDE_DIRS ${INCLUDE_DIR_LIST}
)

# ------ Set the project options ------ #
include(${CMAKE_SOURCE_DIR}/external/CMake/Project.cmake)

project_options()

# ------ Create Demofile ------ #
option(LOG_DEMO_FILE "Build the demo file" ON)

if (LOG_DEMO_FILE)
    message(STATUS "# Create the demofile project")

    set(DEMOFILE_DIR ${MAIN_DIR}/demofile)
    
    add_subdirectory(${DEMOFILE_DIR})
endif()
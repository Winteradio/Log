cmake_minimum_required(VERSION 3.20)
project(LogProject LANGUAGES CXX)

# ------ Create the library ------- #
include(${CMAKE_CURRENT_SOURCE_DIR}/cmake/Library.cmake)

option(BUILD_SHARED_LIBS "Build a shared library instead of a static one" OFF)

set(MAIN_DIR ${CMAKE_CURRENT_SOURCE_DIR})
set(LOG_DIR ${MAIN_DIR}/Log)

set(HEADER_LIST
    ${LOG_DIR}/Log.h
    ${LOG_DIR}/LogConstants.h
    ${LOG_DIR}/LogMessage.h
    ${LOG_DIR}/LogPlatform.h
)

set(SOURCE_LIST
    ${LOG_DIR}/Log.cpp
    ${LOG_DIR}/LogHandler.cpp
    ${LOG_DIR}/LogDefaultHandler.cpp
    ${LOG_DIR}/LogManager.cpp
    ${LOG_DIR}/LogMessage.cpp
    ${LOG_DIR}/LogUtils.cpp
)

create_library(
    SHARED_LIBRARY ${BUILD_SHARED_LIBS}
    TARGET_NAME ${PROJECT_NAME}
    PUBLIC_HEADERS ${HEADER_LIST}
    PRIVATE_SOURCES ${SOURCE_LIST}
)

install_library(
    TARGET_NAME ${PROJECT_NAME}
    PUBLIC_HEADERS ${HEADER_LIST}
    PUBLIC_INCLUDE_DIRS ${LOG_DIR}
)

# ------ Set the project options ------ #
include(${CMAKE_CURRENT_SOURCE_DIR}/cmake/Project.cmake)

project_options()

# ------ Create Demofile ------ #
option(BUILD_DEMO_FILE "Build the demo file" ON)

if (BUILD_DEMO_FILE)
    message(STATUS "# Create the demofile project")

    if (BUILD_SHARED_LIBS)
        set(EXTDEMOFILE_DIR ${MAIN_DIR}/externaldemofile)

        add_subdirectory(${EXTDEMOFILE_DIR})
    else()
        set(DEMOFILE_DIR ${MAIN_DIR}/demofile)
        
        add_subdirectory(${DEMOFILE_DIR})
    endif()
endif()
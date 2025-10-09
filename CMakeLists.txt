cmake_minimum_required(VERSION 3.20)
project(LogProject LANGUAGES CXX)

# ------ Include the cmake modules ------- #
include(${CMAKE_CURRENT_SOURCE_DIR}/cmake/Project.cmake)
include(${CMAKE_CURRENT_SOURCE_DIR}/cmake/Library.cmake)

option(BUILD_SHARED_LIBRARY "Build a shared library instead of a static one" ON)

project_options()
create_library(BUILD_SHARED_LIBRARY ${BUILD_SHARED_LIBRARY})

# ------ Set the build options for the project ------- #
set(MAIN_DIR ${CMAKE_CURRENT_SOURCE_DIR})
set(LOG_DIR ${MAIN_DIR}/Log)

target_sources(${PROJECT_NAME} PUBLIC
    FILE_SET HEADERS
    BASE_DIRS ${LOG_DIR}
    FILES
        ${LOG_DIR}/Log.h
        ${LOG_DIR}/LogConstants.h
        ${LOG_DIR}/LogMessage.h
        ${LOG_DIR}/LogPlatform.h
)

target_sources(${PROJECT_NAME} PRIVATE 
    ${LOG_DIR}/Log.cpp
    
    ${LOG_DIR}/LogHandler.cpp
    ${LOG_DIR}/LogDefaultHandler.cpp
    
    ${LOG_DIR}/LogManager.cpp

    ${LOG_DIR}/LogMessage.cpp

    ${LOG_DIR}/LogUtils.cpp
)

target_include_directories(${PROJECT_NAME} PUBLIC ${LOG_DIR})

install_library(TARGET HEADER_FILES HEADERS)

# ------ Create Demofile ------ #
option(BUILD_DEMO_FILE "Build the demo file" ON)

if (BUILD_DEMO_FILE)
    message(STATUS "# Create the demofile project")

    if (BUILD_SHARED_LIBRARY)
        set(EXTDEMOFILE_DIR ${MAIN_DIR}/externaldemofile)

        add_subdirectory(${EXTDEMOFILE_DIR})
    else()
        set(DEMOFILE_DIR ${MAIN_DIR}/demofile)
        
        add_subdirectory(${DEMOFILE_DIR})
    endif()
endif()
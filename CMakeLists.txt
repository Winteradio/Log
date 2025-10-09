cmake_minimum_required(VERSION 3.20)
project(LogProject LANGUAGES CXX)

# ------ Include the cmake modules ------- #
include(cmake/Project.cmake)
include(cmake/Library.cmake)

project_options()
library_options()

# ------ Set the build options for the project ------- #
set(MAIN_DIR ${CMAKE_SOURCE_DIR})

set(LOG_DIR ${MAIN_DIR}/Log)
set(DEMOFILE_DIR ${MAIN_DIR}/demofile)
set(EXTDEMOFILE_DIR ${MAIN_DIR}/externaldemofile)

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

install(TARGETS ${PROJECT_NAME}
    FILE_SET HEADERS DESTINATION ${INCLUDE_DIR}/${PROJECT_NAME}
)

# ------ Create Demofile ------ #
option(BUILD_DEMO_FILE "Build the demo file" ON)

if (BUILD_DEMO_FILE)
    message(STATUS "# Create the demofile project")
    add_subdirectory(${DEMOFILE_DIR})
    add_subdirectory(${EXTDEMOFILE_DIR})
endif()
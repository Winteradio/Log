# ------ Set the basic options for the demo project ------- #
message(STATUS "Set the basic options for the demo project")

cmake_minimum_required(VERSION 3.20)
project(Demofile LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# ------ Create the executable program ------ #

if (WIN32)
    message(STATUS "Demo Platform : Windows")
    add_executable(${PROJECT_NAME} WIN32)
ELSE ()
    message(STATUS "Demo Platform : Others")
    add_executable(${PROJECT_NAME})
ENDIF()

set(MAIN_DIR ${CMAKE_CURRENT_SOURCE_DIR})

set(HEADER_LIST ${MAIN_DIR}/../Log)

target_sources(${PROJECT_NAME} PRIVATE
    ${MAIN_DIR}/main.cpp

    ${MAIN_DIR}/../Log/Log.h ${MAIN_DIR}/../Log/Log.cpp
    
    ${MAIN_DIR}/../Log/LogConstants.h

    ${MAIN_DIR}/../Log/LogHandler.h ${MAIN_DIR}/../Log/LogHandler.cpp
    ${MAIN_DIR}/../Log/LogDefaultHandler.h ${MAIN_DIR}/../Log/LogDefaultHandler.cpp

    ${MAIN_DIR}/../Log/LogManager.h ${MAIN_DIR}/../Log/LogManager.cpp

    ${MAIN_DIR}/../Log/LogMessage.h ${MAIN_DIR}/../Log/LogMessage.cpp

    ${MAIN_DIR}/../Log/LogPlatform.h
    ${MAIN_DIR}/../Log/LogUtils.h ${MAIN_DIR}/../Log/LogUtils.cpp
)

target_include_directories(${PROJECT_NAME} PUBLIC ${HEADER_LIST})

# ------ Set the basic options for the project ------- #
message(STATUS "# Set the basic options for the project")

cmake_minimum_required(VERSION 3.20)
project(LogProject LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# ------ Set the compiler options for the project ------- #
message(STATUS "# Set the language options for the project")

message(STATUS "Compiler : ${CMAKE_CXX_COMPILER_ID}")

if (CMAKE_CXX_COMPILER_ID STREQUAL "MSVC")
    add_compile_options(/Zi /MP)
elseif (CMAKE_CXX_COMPILER_ID STREQUAL "GNU")
    add_compile_options(-g -Wall -Wextra)
elseif (CMAKE_CXX_COMPILER_ID STREQUAL "Clang")
    add_compile_options(-g -Wall -Wextra)
else()
    message(FATAL_ERROR "The Compiler ${CMAKE_CXX_COMPILER_ID} is not supported")
endif()

if (WIN32)
    message(STATUS "Platform : Windows")
    set(CMAKE_WINDOWS_EXPORT_ALL_SYMBOLS 1)
endif()

# ------ Set the build options for the project ------- #
option(BUILD_SHARED_LIBRARY "Build a shared library instead of a static one" OFF)
option(BUILD_DEMO_FILE "Build the demo file" ON)

set(MAIN_DIR ${CMAKE_SOURCE_DIR})
set(INCLUDE_DIR ${MAIN_DIR}/build/include CACHE PATH "Include files Path")
set(LIB_DIR ${MAIN_DIR}/build/lib CACHE PATH "Library files Path")
set(BIN_DIR ${MAIN_DIR}/build/bin CACHE PATH "Execute files Path")
set(CMAKE_BUILD_TYPE Debug CACHE STRING "Build Type")

set(LOG_DIR ${MAIN_DIR}/Log)
set(DEMOFILE_DIR ${MAIN_DIR}/demofile)
set(EXTDEMOFILE_DIR ${MAIN_DIR}/externaldemofile)

# ------ Create the library ------ #
message(STATUS "# Create the library")

if (BUILD_SHARED_LIBRARY)
    add_library(${PROJECT_NAME} SHARED)
    message(STATUS "The library type is shared")
else()
    add_library(${PROJECT_NAME} STATIC)
    message(STATUS "The library type is static")
endif()

target_sources(${PROJECT_NAME} PUBLIC
    FILE_SET HEADERS
    BASE_DIRS ${LOG_DIR}
    FILES
        ${LOG_DIR}/Log.h
        ${LOG_DIR}/LogConstants.h
        ${LOG_DIR}/LogMessage.h
)

target_sources(${PROJECT_NAME} PRIVATE 
    ${LOG_DIR}/Log.h ${LOG_DIR}/Log.cpp
    
    ${LOG_DIR}/LogConstants.h

    ${LOG_DIR}/LogHandler.h ${LOG_DIR}/LogHandler.cpp
    ${LOG_DIR}/LogDefaultHandler.h ${LOG_DIR}/LogDefaultHandler.cpp
    ${LOG_DIR}/LogManager.h ${LOG_DIR}/LogManager.cpp

    ${LOG_DIR}/LogMessage.h ${LOG_DIR}/LogMessage.cpp

    ${LOG_DIR}/LogUtils.h ${LOG_DIR}/LogUtils.cpp
)

target_include_directories(${PROJECT_NAME} PUBLIC ${LOG_DIR})

install(TARGETS ${PROJECT_NAME}
    RUNTIME DESTINATION ${BIN_DIR}
    ARCHIVE DESTINATION ${LIB_DIR}
    LIBRARY DESTINATION ${LIB_DIR}
    FILE_SET HEADERS DESTINATION ${INCLUDE_DIR}/${PROJECT_NAME}
)

# ------ Create Demofile ------ #
if (BUILD_DEMO_FILE)
    message(STATUS "# Create the demofile project")
    add_subdirectory(${DEMOFILE_DIR})
    add_subdirectory(${EXTDEMOFILE_DIR})
ENDIF()
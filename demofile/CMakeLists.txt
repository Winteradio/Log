# ------ Set Options for Projects --------------- #
MESSAGE( STATUS "Set Options for Project")

## CMake minimum version required
CMAKE_MINIMUM_REQUIRED(VERSION 3.20)
## Set CXX Compiler Version
SET( CMAKE_CXX_STANDARD 17 )

SET( DEMO_NAME "Demofile" )
PROJECT( ${DEMO_NAME} )

MESSAGE( STATUS "Setting Done")
# ----------------------------------------------- #



# ------ Set Files ------------------------------ #
MESSAGE( STATUS "Set File")

IF ( NOT DEFINED DEMO_FOLDER_DIR )
    SET( DEMO_FOLDER_DIR ${CMAKE_SOURCE_DIR} )
ENDIF()

MESSAGE( STATUS "${DEMO_FOLDER_DIR}" )

## Header Files
LIST( APPEND DEMO_FOLDER_LIST 
    ${DEMO_FOLDER_DIR}/../Log 
)

## Source Files
LIST( APPEND DEMO_SOURCE_LIST
    ## Demo file
    ${DEMO_FOLDER_DIR}/main.cpp

    ${DEMO_FOLDER_DIR}/../Log/Log.h ${DEMO_FOLDER_DIR}/../Log/Log.cpp
    
    ${DEMO_FOLDER_DIR}/../Log/LogConstants.h

    ${DEMO_FOLDER_DIR}/../Log/LogHandler.h ${DEMO_FOLDER_DIR}/../Log/LogHandler.cpp
    ${DEMO_FOLDER_DIR}/../Log/LogDefaultHandler.h ${DEMO_FOLDER_DIR}/../Log/LogDefaultHandler.cpp

    ${DEMO_FOLDER_DIR}/../Log/LogManager.h ${DEMO_FOLDER_DIR}/../Log/LogManager.cpp

    ${DEMO_FOLDER_DIR}/../Log/LogMessage.h ${DEMO_FOLDER_DIR}/../Log/LogMessage.cpp

    ${DEMO_FOLDER_DIR}/../Log/LogPlatform.h
    ${DEMO_FOLDER_DIR}/../Log/LogUtils.h ${DEMO_FOLDER_DIR}/../Log/LogUtils.cpp
)

MESSAGE( STATUS "Setting Done ")
# ----------------------------------------------- #



# ------ Link LogProject on Target  ------------- #
MESSAGE(STATUS "Set Options for Target Files")

IF ( WIN32 )
    MESSAGE( STATUS "Windows Platform for demofile")
    ADD_EXECUTABLE( ${DEMO_NAME} WIN32 ${DEMO_SOURCE_LIST} )
    SET( STATIC_LIB lib )
    SET( DYNAMIC_LIB dll )
ELSE ()
    MESSAGE( STATUS "Other Platform for demofile")
    ADD_EXECUTABLE( ${DEMO_NAME} ${DEMO_SOURCE_LIST})
    SET( STATIC_LIB a )
    SET( DYNAMIC_LIB so)
ENDIF()

MESSAGE(STATUS "Setting Done ")
# ----------------------------------------------- #



# ------ Set Executable file -------------------- #
MESSAGE(STATUS "Set Options for Target Files")

TARGET_INCLUDE_DIRECTORIES(${DEMO_NAME} PUBLIC ${DEMO_FOLDER_LIST})

SET( EXE_DIR ${DEMO_FOLDER_DIR}/build )

IF ( CMAKE_BUILD_TYPE MATCHES Debug )
    SET_TARGET_PROPERTIES( ${DEMO_NAME} PROPERTIES
        RUNTIME_OUTPUT_DIRECTORY_DEBUG ${EXE_DIR}/Debug
    )
    MESSAGE( STATUS "Build exe file on Debug mode" )
ELSEIF ( CMAKE_BUILD_TYPE MATCHES Release )
    SET_TARGET_PROPERTIES( ${DEMO_NAME} PROPERTIES
        RUNTIME_OUTPUT_DIRECTORY_RELEASE ${EXE_DIR}/Release
    )
    MESSAGE( STATUS "Build exe file on Release mode" )
ELSE()
    SET_TARGET_PROPERTIES( ${DEMO_NAME} PROPERTIES
        RUNTIME_OUTPUT_DIRECTORY ${EXE_DIR}
    )
    MESSAGE( STATUS "Build exe file on Other mode" )
ENDIF()

MESSAGE( STATUS "Setting Done ")
# ----------------------------------------------- #

ADD_DEFINITIONS( -DTEST_PATH="${EXE_DIR}")

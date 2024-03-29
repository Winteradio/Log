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
MESSAGE( STATUS "Set Source File")

IF ( NOT DEFINED DEMOFILE_DIR )
    SET( DEMOFILE_DIR ${CMAKE_SOURCE_DIR} )
ENDIF()

## Source Files
LIST( APPEND SRCS
    ## Demo file
    ${DEMOFILE_DIR}/main.cpp
	)

MESSAGE( STATUS "Setting Done ")
# ----------------------------------------------- #



# ------ Set Options for Target Files ----------- #
MESSAGE( STATUS "Add Executable by platform")

## Include Header Directories for Target Files
IF ( WIN32 )
    MESSAGE( STATUS "Windows Platform for demofile")
    ADD_EXECUTABLE( ${DEMO_NAME} WIN32 ${SRCS} )
    SET( STATIC_LIB lib )
    SET( DYNAMIC_LIB dll )
ELSE ()
    MESSAGE( STATUS "Other Platform for demofile")
    ADD_EXECUTABLE( ${DEMO_NAME} ${SRCS} )
    SET( STATIC_LIB a )
    SET( DYNAMIC_LIB so )
ENDIF()

MESSAGE( STATUS "Setting Done" )
# ----------------------------------------------- #



# ------ Download LogProject in Github ---------- #
MESSAGE( STATUS "Download LogProject" )

INCLUDE( ExternalProject )

SET( DEP_INCLUDE )
SET( DEP_LIB_DIR )
SET( DEP_LIBS )
SET( DEP_LIST )

SET( DEMO_INCLUDE_DIR ${DEMOFILE_DIR}/build/include )
SET( DEMO_LIB_DIR ${DEMOFILE_DIR}/build/lib )
SET( DEMO_BIN_DIR ${DEMOFILE_DIR}/build/Debug )
SET( DEMO_ARC_DIR ${DEMOFILE_DIR}/build/arc )

SET( PROJECTLIST )

SET( PROJECT LogProject )

LIST( APPEND PROJECTLIST PROJECT )

EXTERNALPROJECT_ADD(
	${PROJECT}
	GIT_REPOSITORY GIT_REPOSITORY https://github.com/Winteradio/Log.git
	GIT_TAG "v2.3.0"

	PREFIX ${CMAKE_BINARY_DIR}/Prefix/${PROJECT}

	UPDATE_COMMAND "" PATCH_COMMAND "" TEST_COMMAND "" INSTALL_COMMAND ""
	CMAKE_ARGS 
		-DINCLUDE_DIR=${DEMO_INCLUDE_DIR}
		-DLIB_DIR=${DEMO_LIB_DIR}
		-DBIN_DIR=${DEMO_BIN_DIR}
        -DARC_DIR=${DEMO_ARC_DIR}
		-DCMAKE_BUILD_TYPE=Debug
		-DBUILD_STATIC_LIBRARY=OFF
 		-DINSTALL_DEMO_FILE=OFF 
)

LIST( APPEND DEP_LIST ${PROJECT} )
LIST( APPEND DEP_INCLUDE ${DEMO_INCLUDE_DIR} )
LIST( APPEND DEP_LIBS ${DEMO_ARC_DIR}/${PROJECT}.${STATIC_LIB} )

MESSAGE( STATUS "Downloading Done" )
# ----------------------------------------------- #



# ------ Link LogProject on Target  ------------- #
MESSAGE(STATUS "Set Options for Target Files")

TARGET_INCLUDE_DIRECTORIES(${PROJECT_NAME} PUBLIC ${DEP_INCLUDE})
TARGET_LINK_DIRECTORIES(${PROJECT_NAME} PUBLIC ${DEMO_LIB_DIR} ${DEP_LIB_DIR} )
TARGET_LINK_LIBRARIES(${PROJECT_NAME} PUBLIC ${DEP_LIBS})
ADD_DEPENDENCIES(${PROJECT_NAME} ${DEP_LIST})

MESSAGE(STATUS "Setting Done ")
# ----------------------------------------------- #



# ------ Set Executable file -------------------- #
MESSAGE(STATUS "Set Options for Target Files")

SET( EXE_DIR ${DEMOFILE_DIR}/build )

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
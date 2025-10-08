# ------ Set the basic options for the demo project ------- #
message(STATUS "Set the basic options for the demo project")

cmake_minimum_required(VERSION 3.20)
project(ExtDemofile LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

include(ExternalProject)

# ------ Create the executable program ------ #

if (WIN32)
    message(STATUS "Demo Platform : Windows")
    add_executable(${PROJECT_NAME} WIN32)

    set(STATIS_LIBRARY lib)
    set(SHARED_LIBRARY dll)
ELSE ()
    message(STATUS "Demo Platform : Others")
    add_executable(${PROJECT_NAME})

    set(STATIS_LIBRARY a)
    set(SHARED_LIBRARY so)
ENDIF()

# ------ Load the log project ------ #
message(STATUS "Download : LogProject")

set_target_properties(${PROJECT_NAME} PROPERTIES
    RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}
)

set(EXT_INCLUDE_DIR ${CMAKE_BINARY_DIR}/include)
set(EXT_LIB_DIR ${CMAKE_BINARY_DIR}/lib)
set(EXT_BIN_DIR ${RUNTIME_OUTPUT_DIRECTORY})
set(EXT_LIBRARIES)
set(EXT_LIST)

EXTERNALPROJECT_ADD(
	LogProject_Add
	GIT_REPOSITORY GIT_REPOSITORY https://github.com/Winteradio/Log.git
    GIT_TAG CMAKE_TEST

	PREFIX ${CMAKE_BINARY_DIR}/Prefix/LogProject_Add

	UPDATE_COMMAND "" PATCH_COMMAND "" TEST_COMMAND ""
	CMAKE_ARGS 
		-DINCLUDE_DIR=${EXT_INCLUDE_DIR}
		-DLIB_DIR=${EXT_LIB_DIR}
		-DBIN_DIR=${EXT_BIN_DIR}
		-DCMAKE_BUILD_TYPE=Debug
		-DBUILD_SHARED_LIBRARY=ON
 		-DBUILD_DEMO_FILE=OFF
)

list(APPEND ${EXT_LIST} LogProject_Add)
list(APPEND ${EXT_LIBRARIES} ${EXT_LIB_DIR}/LogProject.${STATIC_LIBRARY})

# ------ Set the properties the executable program ------ #

target_sources(${PROJECT_NAME} PRIVATE
    ${CMAKE_CURRENT_SOURCE_DIR}/main.cpp
)

target_include_directories(${PROJECT_NAME} PUBLIC
    ${CMAKE_BINARY_DIR}/include
)

target_link_libraries(${PROJECT_NAME} PUBLIC 
    ${CMAKE_BINARY_DIR}/${LIB_DIR}/LogProject.lib
)

add_dependencies(${PROJECT_NAME} LogProject_Add)
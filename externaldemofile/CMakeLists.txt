# ------ Set the basic options for the demo project ------- #
message(STATUS "# Set the basic options for the external demo project")

cmake_minimum_required(VERSION 3.20)
project(ExtDemofile LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

include(ExternalProject)

# ------ Create the executable program ------ #

if (WIN32)
    message(STATUS "Demo Platform : Windows")
    add_executable(${PROJECT_NAME} WIN32)

    set(STATIC_LIBRARY lib)
    set(SHARED_LIBRARY dll)
ELSE ()
    message(STATUS "Demo Platform : Others")
    add_executable(${PROJECT_NAME})

    set(STATIC_LIBRARY a)
    set(SHARED_LIBRARY so)
ENDIF()

# ------ Load the log project ------ #
message(STATUS "# Download : LogProject")

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}/${CMAKE_BUILD_TYPE})

set(EXT_INCLUDE_DIR ${CMAKE_CURRENT_BINARY_DIR}/include)
set(EXT_LIB_DIR ${CMAKE_CURRENT_BINARY_DIR}/lib)
set(EXT_BIN_DIR ${CMAKE_RUNTIME_OUTPUT_DIRECTORY})

EXTERNALPROJECT_ADD(
	LogProject_Add
	GIT_REPOSITORY GIT_REPOSITORY https://github.com/Winteradio/Log.git
    GIT_TAG CMAKE_TEST

	PREFIX ${CMAKE_CURRENT_BINARY_DIR}/Prefix/LogProject_Add

	UPDATE_COMMAND "" PATCH_COMMAND "" TEST_COMMAND ""
	CMAKE_ARGS 
		-DINCLUDE_DIR=${EXT_INCLUDE_DIR}
		-DLIB_DIR=${EXT_LIB_DIR}
		-DBIN_DIR=${EXT_BIN_DIR}
		-DCMAKE_BUILD_TYPE=Debug
		-DBUILD_SHARED_LIBRARY=ON
 		-DBUILD_DEMO_FILE=OFF
)

set(EXT_LIST LogProject_Add)
set(EXT_LIBRARIES ${EXT_LIB_DIR}/LogProject.${STATIC_LIBRARY})

# ------ Set the properties the executable program ------ #

target_sources(${PROJECT_NAME} PRIVATE
    ${CMAKE_CURRENT_SOURCE_DIR}/main.cpp
)

target_include_directories(${PROJECT_NAME} PUBLIC ${EXT_INCLUDE_DIR})
target_link_directories(${PROJECT_NAME} PUBLIC ${EXT_LIB_DIR})
target_link_libraries(${PROJECT_NAME} PUBLIC ${EXT_LIBRARIES})

add_dependencies(${PROJECT_NAME} LogProject_Add)
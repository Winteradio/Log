# ------ Set the variables for the library options ------- #
message(STATUS "Set the options for the library")

option(BUILD_SHARED_LIBRARY "Build a shared library instead of a static one" OFF)

set(INCLUDE_DIR ${CMAKE_BINARY_DIR}/include CACHE PATH "Include files Path")
set(LIB_DIR ${CMAKE_BINARY_DIR}/lib CACHE PATH "Library files Path")
set(BIN_DIR ${CMAKE_BINARY_DIR}/bin CACHE PATH "Execute files Path")

# ------ Set the options for the library ------- #
function(library_options)
	message(STATUS "# Create the library")
	message(STATUS "# The Library Type : ${BUILD_SHARED_LIBRARY}")
	message(STATUS "# The Binary Directory : ${LIB_DIR}")
	message(STATUS "# The Library Directory : ${BIN_DIR}")
	message(STATUS "# The Include Directory : ${INCLUDE_DIR}")

	if (${BUILD_SHARED_LIBRARY} STREQUAL "SHARED")
	    add_library(${PROJECT_NAME} SHARED)
	else()
	    add_library(${PROJECT_NAME} STATIC)
	endif()

	install(TARGETS ${PROJECT_NAME}
	    RUNTIME DESTINATION ${BIN_DIR}
	    ARCHIVE DESTINATION ${LIB_DIR}
	    LIBRARY DESTINATION ${LIB_DIR}
	    FILE_SET HEADERS DESTINATION ${INCLUDE_DIR}/${PROJECT_NAME}
	)
endfunction()



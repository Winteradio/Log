# ------ Set the variables for the library options ------- #
message(STATUS "# Set the options for the library")

set(INCLUDE_DIR ${CMAKE_BINARY_DIR}/include CACHE PATH "Include files Path")
set(LIB_DIR ${CMAKE_BINARY_DIR}/lib CACHE PATH "Library files Path")
set(BIN_DIR ${CMAKE_BINARY_DIR}/bin CACHE PATH "Execute files Path")

# ------ Set the options for the library ------- #
function(create_library)
	cmake_parse_arguments(
		ARG # Options / Single Value / Multi Value
		"BUILD_SHARED_LIBRARY"	
		""
		""
		${ARGN})

	message(STATUS "# Create the library")
	message(STATUS "- The Library Type : ${BUILD_SHARED_LIBRARY}")
	message(STATUS "- The Binary Directory : ${BIN_DIR}")
	message(STATUS "- The Library Directory : ${LIB_DIR}")
	message(STATUS "- The Include Directory : ${INCLUDE_DIR}")

	if (${ARG_BUILD_SHARED_LIBRARY})
		message(STATUS "# Create the shared library")

		add_library(${PROJECT_NAME} SHARED)

		if (WIN32)
			set_target_properties(${PROJECT_NAME} PROPERTIES WINDOWS_EXPORT_ALL_SYMBOLS ON)			
		endif()
	else()
		message(STATUS "# Create the static library")

	    add_library(${PROJECT_NAME} STATIC)
	endif()

endfunction()

# ------ Copy the public header files for the library ------- #
function(install_library)
	cmake_parse_arguments(
		ARG # Options / Single Value / Multi Value
		""	
		""
		"HEADER_FILES"
		${ARGN})

	if (NOT ARG_HEADER_FILES)
		message(WARNING "# Warning : No header files to copy")

		set(ARG_HEADER_FILES "")
	endif()

	message(STATUS "# Install the library")
	message(STATUS "- The binary Path : ${BIN_DIR}")
	message(STATUS "- The library Path : ${LIB_DIR}")
	message(STATUS "- The include Path : ${INCLUDE_DIR}")

	target_include_directories(${PROJECT_NAME} PUBLIC ${INCLUDE_DIR})

	install(TARGETS ${PROJECT_NAME}
		RUNTIME DESTINATION ${BIN_DIR}
		ARCHIVE DESTINATION ${LIB_DIR}
		LIBRARY DESTINATION ${LIB_DIR}
		FILE_SET ${ARG_HEADER_FILES} DESTINATION ${INCLUDE_DIR}/${PROJECT_NAME})

endfunction()



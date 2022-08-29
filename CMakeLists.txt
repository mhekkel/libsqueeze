#          Copyright Maarten L. Hekkelman, 2022
# Distributed under the Boost Software License, Version 1.0.
#    (See accompanying file LICENSE_1_0.txt or copy at
#          http://www.boost.org/LICENSE_1_0.txt)

cmake_minimum_required(VERSION 3.16)

# set the project name
project(squeeze VERSION 1.0.0)

include(GNUInstallDirs)
include(CMakePackageConfigHelpers)
include(FindPkgConfig)

set(CXX_EXTENSIONS OFF)
set(CMAKE_CXX_STANDARD 17 CACHE STRING "The minimum version of C++ required for this library")
set(CMAKE_CXX_STANDARD_REQUIRED ON)

if("${CMAKE_CXX_COMPILER_ID}" STREQUAL "GNU")
	set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Wextra -Wno-unused-parameter -Wno-missing-field-initializers")
elseif(MSVC)
    set(CMAKE_CXX_FLAGS  "${CMAKE_CXX_FLAGS} /W4")

	# make msvc standards compliant...
    add_compile_options(/permissive-)
endif()

add_library(squeeze INTERFACE)
add_library(squeeze::squeeze ALIAS squeeze)

target_include_directories(squeeze INTERFACE
	$<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
	$<INSTALL_INTERFACE:include>
)

# adding header sources just helps IDEs
target_sources(squeeze INTERFACE
	$<BUILD_INTERFACE:${CMAKE_CURRENT_LIST_DIR}/include>$<INSTALL_INTERFACE:include>/squeeze.hpp
)

set_target_properties(squeeze PROPERTIES PUBLIC_HEADER include/squeeze.hpp)

# installation
set(version_config "${CMAKE_CURRENT_BINARY_DIR}/squeezeConfigVersion.cmake")

set(INCLUDE_INSTALL_DIR ${CMAKE_INSTALL_INCLUDEDIR})

include(CMakePackageConfigHelpers)
write_basic_package_version_file("${version_config}"
	VERSION ${PROJECT_VERSION}
	COMPATIBILITY SameMajorVersion)

install(TARGETS squeeze
	EXPORT squeezeConfig
	PUBLIC_HEADER DESTINATION ${CMAKE_INSTALL_INCLUDEDIR})

export(TARGETS squeeze NAMESPACE squeeze:: FILE squeezeTargets.cmake)

if(WIN32 AND NOT CYGWIN)
	set(CONFIG_LOC CMake)
else()
	set(CONFIG_LOC "${CMAKE_INSTALL_LIBDIR}/cmake/squeeze")
endif()

configure_package_config_file(
	${CMAKE_SOURCE_DIR}/cmake/squeezeConfig.cmake.in
	${CMAKE_SOURCE_DIR}/cmake/squeezeConfig.cmake
	INSTALL_DESTINATION ${CMAKE_INSTALL_LIBDIR}/cmake/squeeze
	PATH_VARS INCLUDE_INSTALL_DIR
)

install(EXPORT squeezeConfig
	FILE squeezeTargets.cmake
	NAMESPACE squeeze::
	DESTINATION ${CONFIG_LOC})
install(
	FILES cmake/squeezeConfig.cmake "${version_config}"
	DESTINATION ${CONFIG_LOC})

if(ENABLE_TESTING)
	enable_testing()

	find_package(Boost 1.70.0 REQUIRED headers)

	add_executable(unit-test ${PROJECT_SOURCE_DIR}/unit-test.cpp)

	target_link_libraries(unit-test squeeze::squeeze Boost::headers)

	if(MSVC)
		# Specify unwind semantics so that MSVC knowns how to handle exceptions
		target_compile_options(unit-test PRIVATE /EHsc)
	endif()

	add_test(NAME unit-test COMMAND $<TARGET_FILE:unit-test>)
endif(ENABLE_TESTING)



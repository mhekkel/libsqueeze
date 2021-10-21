# Copyright (c) 2021 Maarten L. Hekkelman

# Redistribution and use in source and binary forms, with or without
# modification, are permitted provided that the following conditions are met:

# 1. Redistributions of source code must retain the above copyright notice, this
#    list of conditions and the following disclaimer
# 2. Redistributions in binary form must reproduce the above copyright notice,
#    this list of conditions and the following disclaimer in the documentation
#    and/or other materials provided with the distribution.

# THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND
# ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED
# WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
# DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT OWNER OR CONTRIBUTORS BE LIABLE FOR
# ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES
# (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES;
# LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND
# ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
# (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS
# SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.

cmake_minimum_required(VERSION 3.10)

list(APPEND CMAKE_MODULE_PATH "${CMAKE_CURRENT_SOURCE_DIR}/cmake")

# set the project name
project(squeeze VERSION 1.0.0)

include(CMakePackageConfigHelpers)
include(Dart)
include(GenerateExportHeader)
include(GNUInstallDirs)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(Boost 1.70.0 REQUIRED)

add_executable(unit-test ${PROJECT_SOURCE_DIR}/unit-test.cpp)
target_include_directories(unit-test PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/include)

enable_testing()

add_test(NAME unit-test COMMAND $<TARGET_FILE:unit-test>)

# if(WIN32)
# 	install(FILES mrc-config.cmake DESTINATION cmake)
# 	install(FILES mrc-manual.pdf DESTINATION doc)
# else()
# 	install(FILES mrc-config.cmake DESTINATION share/mrc/cmake)
# 	install(FILES mrc.1 DESTINATION share/man/man1)
# endif()

add_library(squeeze INTERFACE)

set(INCLUDE_INSTALL_DIR ${CMAKE_INSTALL_INCLUDEDIR} )

install(TARGETS squeeze
	EXPORT squeeze-targets
	ARCHIVE DESTINATION ${CMAKE_INSTALL_LIBDIR}
	LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
	RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
	INCLUDES DESTINATION ${CMAKE_INSTALL_INCLUDEDIR})

install(EXPORT squeeze-targets
	FILE "squeeze-targets.cmake"
	NAMESPACE squeeze::
	DESTINATION ${CMAKE_INSTALL_LIBDIR}/cmake/squeeze
)

install(
	DIRECTORY include/sq
	DESTINATION ${CMAKE_INSTALL_INCLUDEDIR}
	COMPONENT Devel
)

configure_package_config_file(squeeze-config.cmake.in
	${CMAKE_CURRENT_BINARY_DIR}/squeeze/squeeze-config.cmake
	INSTALL_DESTINATION ${CMAKE_INSTALL_LIBDIR}/cmake/squeeze
	PATH_VARS INCLUDE_INSTALL_DIR
)

install(FILES
		"${CMAKE_CURRENT_BINARY_DIR}/squeeze/squeeze-config.cmake"
		"${CMAKE_CURRENT_BINARY_DIR}/squeeze/squeeze-config-version.cmake"
	DESTINATION ${CMAKE_INSTALL_LIBDIR}/cmake/squeeze
	COMPONENT Devel
)

set(squeeze_MAJOR_VERSION 1)
set_target_properties(squeeze PROPERTIES
	INTERFACE_squeeze_MAJOR_VERSION ${squeeze_MAJOR_VERSION})

set_property(TARGET squeeze APPEND PROPERTY
  COMPATIBLE_INTERFACE_STRING squeeze_MAJOR_VERSION
)

write_basic_package_version_file(
  "${CMAKE_CURRENT_BINARY_DIR}/squeeze/squeeze-config-version.cmake"
  VERSION ${PROJECT_VERSION}
  COMPATIBILITY AnyNewerVersion
)


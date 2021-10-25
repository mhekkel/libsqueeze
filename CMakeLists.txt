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

find_package(Boost 1.70.0 REQUIRED headers)

add_executable(unit-test ${PROJECT_SOURCE_DIR}/unit-test.cpp)
target_include_directories(unit-test PRIVATE ${Boost_INCLUDE_DIRS} ${CMAKE_CURRENT_SOURCE_DIR}/include)

enable_testing()

add_test(NAME unit-test COMMAND $<TARGET_FILE:unit-test>)

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


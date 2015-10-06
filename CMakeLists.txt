cmake_minimum_required (VERSION 3.3.2)
project (YX5300-mp3-control)

set (CMAKE_CXX_FLAGS "-Wall -std=gnu++11")

set (VERSION_MAJOR 1)
set (VERSION_MINOR 0)

configure_file (
	"${PROJECT_SOURCE_DIR}/Config.h.in"
	"${PROJECT_BINARY_DIR}/Config.h"
	)

include_directories (
	"${PROJECT_SOURCE_DIR}"
	"${PROJECT_BINARY_DIR}"
	"arap-utils/"
	)

file(GLOB SOURCES "*.cpp" "arap-utils/ArapUtils.cpp")

add_executable(YX5300-control ${SOURCES})

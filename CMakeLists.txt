PROJECT(CertViewer CXX)

cmake_minimum_required(VERSION 3.4)

find_package(PkgConfig REQUIRED)
pkg_check_modules(GTKMM REQUIRED gtkmm-3.0)

include_directories(${GTKMM_INCLUDE_DIRS})
link_directories(${GTKMM_LIBRARY_DIRS})

add_definitions(${GTKMM_CFLAGS_OTHER})

ADD_EXECUTABLE(certviewer main.cpp)
set_target_properties(certviewer PROPERTIES
	CXX_STANDARD 11
	RUNTIME_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/bin"
)
TARGET_LINK_LIBRARIES(certviewer ${GTKMM_LIBRARIES})

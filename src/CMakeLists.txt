find_package(PkgConfig REQUIRED)
pkg_check_modules(GTKMM REQUIRED gtkmm-3.0)

file(GLOB SOURCES "*.cpp")
add_executable(certviewer ${SOURCES})

include_directories("../lib")
include_directories(${GTKMM_INCLUDE_DIRS})
include_directories(${CMAKE_BINARY_DIR}/lib)

link_directories(${GTKMM_LIBRARY_DIRS})

add_definitions(${GTKMM_CFLAGS_OTHER})

set_target_properties(certviewer PROPERTIES
    CXX_STANDARD 11
    RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}
)

target_link_libraries(certviewer ${GTKMM_LIBRARIES} pkiutils)


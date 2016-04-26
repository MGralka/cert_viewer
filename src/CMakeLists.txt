add_executable(certviewer main.cpp mainwindow.cpp)

set_target_properties(certviewer PROPERTIES
	CXX_STANDARD 11
	RUNTIME_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/bin"
)
target_link_libraries(certviewer ${GTKMM_LIBRARIES})

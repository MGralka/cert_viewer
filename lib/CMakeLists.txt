find_package(OpenSSL REQUIRED)

file(GLOB SOURCES "*.cpp")
add_library(pkiutils SHARED ${SOURCES})
target_link_libraries(pkiutils ${OPENSSL_LIBRARIES})

set_target_properties(pkiutils PROPERTIES
    CXX_STANDARD 11
    LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}
)

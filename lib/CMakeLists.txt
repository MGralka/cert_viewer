find_package(OpenSSL REQUIRED)

add_library(pkiutils SHARED certificate.cpp)
target_link_libraries(pkiutils ${OPENSSL_LIBRARIES})

set_target_properties(pkiutils PROPERTIES
    CXX_STANDARD 11
    LIBRARY_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/bin"
)

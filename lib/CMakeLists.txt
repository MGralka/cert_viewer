add_library(pkiutils SHARED certificate.cpp)

set_target_properties(pkiutils PROPERTIES
    CXX_STANDARD 11
    LIBRARY_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/bin"
)

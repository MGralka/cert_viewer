cmake_minimum_required(VERSION 3.4)

project(CertViewer CXX)

find_package(OpenSSL REQUIRED)
add_subdirectory(src)


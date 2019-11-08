cmake_minimum_required(VERSION 3.5)

project(QLibBsarch LANGUAGES CXX)

set(CMAKE_INCLUDE_CURRENT_DIR ON)
find_package(Qt5 COMPONENTS Core REQUIRED)

add_library(QLibBsarch STATIC
    BSArchive.cpp
    BSArchive.h
    BSArchiveAuto.cpp
    BSArchiveAuto.h
    BSArchiveEntries.cpp
    BSArchiveEntries.h
    dds.h
    libbsarch.h
    QLibBsarch.hpp
)

target_link_libraries(QLibBsarch PRIVATE Qt5::Core)

target_compile_definitions(QLibBsarch PRIVATE QLIBBSARCH_LIBRARY)
target_compile_features(QLibBsarch PUBLIC cxx_std_17)

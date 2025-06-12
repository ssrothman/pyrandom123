cmake_minimum_required(VERSION 3.15...3.26)
project(${SKBUILD_PROJECT_NAME} LANGUAGES CXX)

set(PYBIND11_FINDPYTHON ON)
find_package(pybind11 CONFIG REQUIRED)

pybind11_add_module(_philox2x32 MODULE src/main.cpp)
target_include_directories(_philox2x32 PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/src/random123/include)
install(TARGETS _philox2x32 DESTINATION ${SKBUILD_PROJECT_NAME})

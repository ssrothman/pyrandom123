cmake_minimum_required(VERSION 3.15...3.26)
project(${SKBUILD_PROJECT_NAME} LANGUAGES CXX)

set(PYBIND11_FINDPYTHON ON)
find_package(pybind11 CONFIG REQUIRED)

#extern random123 library headers
file(GLOB_RECURSE RANDOM123_HEADERS_CPP "extern/random123/include/*.hpp")
file(GLOB_RECURSE RANDOM123_HEADERS_C "extern/random123/include/*.h")

#headers and source for my bindings
file(GLOB_RECURSE PYRANDOM123_HEADERS "include/pyrandom123/*.hpp")
file(GLOB_RECURSE PYRANDOM123_SRC CONFIGURE_DEPENDS src/*.cpp)

#define the python module
pybind11_add_module(_core MODULE ${RANDOM123_HEADERS_C} ${RANDOM123_HEADERS_CPP} ${PYRANDOM123_HEADERS} ${PYRANDOM123_SRC})

#setup includes for the extern random123 library
target_include_directories(_core SYSTEM PUBLIC extern/random123/include)

#setup includes for my bindings
target_include_directories(_core PRIVATE include)

# Better error messages
target_compile_definitions(_core PRIVATE PYBIND11_DETAILED_ERROR_MESSAGES)

install(TARGETS _core DESTINATION ${SKBUILD_PROJECT_NAME})

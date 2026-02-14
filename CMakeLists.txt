cmake_minimum_required(VERSION 3.10.0)
project(build-me-a-container VERSION 0.1.0 LANGUAGES C CXX)

add_executable(build-me-a-container src/main.cpp)

include(CTest)
enable_testing()

set(CPACK_PROJECT_NAME ${PROJECT_NAME})
set(CPACK_PROJECT_VERSION ${PROJECT_VERSION})
include(CPack)

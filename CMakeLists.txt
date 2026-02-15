cmake_minimum_required(VERSION 3.10.0)
project(build-me-a-container VERSION 0.1.0 LANGUAGES C CXX)

add_executable(build-me-a-container src/main.cpp)

include(CTest)
enable_testing()

include(InstallRequiredSystemLibraries)
set(CPACK_PACKAGE_NAME "build-me-a-container")
set(CPACK_PACKAGE_VENDOR "angrypig555")
set(CPACK_PACKAGE_CONTACT "angrypig555 <brny@brny.dev>")
set(CPACK_DEBIAN_PACKAGE_DEPENDS "libc6 (>= 2.17), libstdc++6 (>= 5.2)")
set(CPACK_DEBIAN_FILE_NAME DEB-DEFAULT)
set(CPACK_PACKAGE_DESCRIPTION_SUMMARY "A dockerfile and docker compose generator with an interactive cli")
set(CPACK_RESOURCE_FILE_LICENSE "${CMAKE_CURRENT_SOURCE_DIR}/LICENSE")
set(CPACK_PACKAGE_VERSION_MAJOR "0")
set(CPACK_PACKAGE_VERSION_MINOR "1")
install(TARGETS build-me-a-container DESTINATION bin)

set(CPACK_GENERATOR "DEB;RPM;TGZ")

set(CPACK_PROJECT_NAME ${PROJECT_NAME})
set(CPACK_PROJECT_VERSION ${PROJECT_VERSION})
include(CPack)

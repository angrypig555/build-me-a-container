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
set(CPACK_PACKAGE_VERSION_MINOR "2")
install(TARGETS build-me-a-container DESTINATION bin)

find_program(PANDOC pandoc)
if(NOT PANDOC)
    message(WARNING "Pandoc not found, skipping man page generation.")
endif()

set(MAN_SRC "${CMAKE_CURRENT_SOURCE_DIR}/docs/build-me-a-container.1.md")
set(MAN_OUT "${CMAKE_CURRENT_BINARY_DIR}/build-me-a-container.1")

add_custom_command(
    OUTPUT ${MAN_OUT}
    COMMAND ${PANDOC} -s -t man ${MAN_SRC} -o ${MAN_OUT}
    DEPENDS ${MAN_SRC}
    COMMENT "Generating groff man page"
)

add_custom_target(generate_man ALL DEPENDS ${MAN_OUT})
install(FILES ${MAN_OUT} DESTINATION share/man/man1 COMPONENT documentation)
set(CPACK_GENERATOR "DEB;RPM;TGZ")

set(CPACK_PROJECT_NAME ${PROJECT_NAME})
set(CPACK_PROJECT_VERSION ${PROJECT_VERSION})
include(CPack)

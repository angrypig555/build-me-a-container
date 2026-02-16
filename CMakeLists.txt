cmake_minimum_required(VERSION 3.10.0)
project(build-me-a-container VERSION 1.0.0 LANGUAGES C CXX)

add_executable(build-me-a-container src/main.cpp)

include(CTest)
enable_testing()

set(CPACK_PACKAGING_INSTALL_PREFIX "/usr")
include(InstallRequiredSystemLibraries)
set(CPACK_PACKAGE_NAME "build-me-a-container")
set(CPACK_PACKAGE_VENDOR "angrypig555")
set(CPACK_PACKAGE_CONTACT "angrypig555 <brny@brny.dev>")
set(CPACK_DEBIAN_PACKAGE_DEPENDS "libc6 (>= 2.17), libstdc++6 (>= 5.2)")
set(CPACK_DEBIAN_FILE_NAME DEB-DEFAULT)
set(CPACK_PACKAGE_DESCRIPTION_SUMMARY "A dockerfile and docker compose generator with an interactive cli")
set(CPACK_PACKAGE_DESCRIPTION "A dockerfile and docker compose generator with an interactive cli, podman and docker support.")
set(CPACK_RPM_PACKAGE_DESCRIPTION "A dockerfile and docker compose generator with an interactive cli, podman and docker support.")
set(CPACK_RESOURCE_FILE_LICENSE "${CMAKE_CURRENT_SOURCE_DIR}/LICENSE")
set(CPACK_PACKAGE_VERSION_MAJOR "1")
set(CPACK_PACKAGE_VERSION_MINOR "0")
set(CPACK_RPM_PACKAGE_LICENSE "GPL-3.0-only")
set(CPACK_DEBIAN_PACKAGE_LICENSE "GPL-3.0-only")
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
message(INFO "Packing metadata...")
install(FILES "docs/dev.brny.angrypig555.build-me-a-container.metainfo.xml" DESTINATION "share/metainfo" COMPONENT Runtime)


set(CPACK_PROJECT_NAME ${PROJECT_NAME})
set(CPACK_PROJECT_VERSION ${PROJECT_VERSION})
include(CPack)

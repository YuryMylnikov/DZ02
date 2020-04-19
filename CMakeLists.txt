cmake_minimum_required(VERSION 3.2)

project(IPFilter VERSION 0.0.$ENV{TRAVIS_BUILD_NUMBER)

configure_file(version.h.in version.h)

add_executable(IPFilter main.cpp)

set_target_properties(IPFilter PROPERTIES
    CXX_STANDARD 14
    CXX_STANDARD_REQUIRED ON
)

if (MSVC)
    target_compile_options(IPFilter PRIVATE
        /W4
    )
else ()
    target_compile_options(IPFilter PRIVATE
        -Wall -Wextra -pedantic -Werror
    )
endif()

install(TARGETS IPFilter RUNTIME DESTINATION bin)

set(CPACK_GENERATOR DEB)

set(CPACK_PACKAGE_VERSION_MAJOR "${PROJECT_VERSION_MAJOR}")
set(CPACK_PACKAGE_VERSION_MINOR "${PROJECT_VERSION_MINOR}")
set(CPACK_PACKAGE_VERSION_PATCH "${PROJECT_VERSION_PATCH}")

set(CPACK_PACKAGE_CONTACT example@example.com)

include(CPack)
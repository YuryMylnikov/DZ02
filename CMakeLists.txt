cmake_minimum_required(VERSION 3.2)

project(IPFilter VERSION 0.0.$ENV{TRAVIS_BUILD_NUMBER})

add_executable(IPFilter main.cpp)
add_library(IPPool IPPool.cpp IPv4Address.cpp Tokenizer.cpp)

set_target_properties(IPFilter IPPool PROPERTIES
    CXX_STANDARD 14
    CXX_STANDARD_REQUIRED ON
)

target_include_directories(IPPool
    PRIVATE "${CMAKE_BINARY_DIR}"
)

target_link_libraries(IPFilter PRIVATE
    IPPool
)

if (MSVC)
    target_compile_options(IPFilter IPPool PRIVATE
        /W4
    )
else ()
    target_compile_options(IPFilter IPPool PRIVATE
        -Wall -Wextra -pedantic -Werror
    )
endif()

install(TARGETS IPFilter RUNTIME DESTINATION bin)

set(CPACK_GENERATOR DEB)

set(CPACK_PACKAGE_VERSION_MAJOR "${PROJECT_VERSION_MAJOR}")
set(CPACK_PACKAGE_VERSION_MINOR "${PROJECT_VERSION_MINOR}")
set(CPACK_PACKAGE_VERSION_PATCH "${PROJECT_VERSION_PATCH}")

include(CPack)
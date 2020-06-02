cmake_minimum_required(VERSION 3.2)

if($ENV{TRAVIS_BUILD_NUMBER})
    set(VERSION 0.0.$ENV{TRAVIS_BUILD_NUMBER})
else()
    set(VERSION 0.0.0)
endif()

project(ip_filter VERSION ${VERSION})

add_executable(IPFilter main.cpp)
add_library(IPPool IPPool.cpp IPv4Address.cpp Tokenizer.cpp)

set_target_properties(IPFilter IPPool PROPERTIES
    CXX_STANDARD 14
    CXX_STANDARD_REQUIRED ON
)

target_link_libraries(IPFilter PRIVATE
    IPPool
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
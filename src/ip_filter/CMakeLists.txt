add_library(filter_lib  ip_filter.cpp)

set_target_properties(filter_lib  PROPERTIES
    CXX_STANDARD 17
    CXX_STANDARD_REQUIRED ON )

target_include_directories(filter_lib
    PRIVATE "${CMAKE_CURRENT_SOURCE_DIR}"
)

if (MSVC)
    target_compile_options(filter_lib PRIVATE
        /W4
    )
else ()
    target_compile_options(filter_lib PRIVATE
        -Wall -Wextra -pedantic -Werror
    )
endif()

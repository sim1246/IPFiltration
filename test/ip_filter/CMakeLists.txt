add_executable(gtests gtest_version.cpp)
    
set_target_properties(gtests PROPERTIES
        CXX_STANDARD 17
        CXX_STANDARD_REQUIRED ON )

target_include_directories(gtests PUBLIC 
    "${CMAKE_SOURCE_DIR}/src/ip_filter"
)
target_link_libraries(gtests gtest_main filter_lib)

include(GoogleTest)
gtest_discover_tests(gtests)

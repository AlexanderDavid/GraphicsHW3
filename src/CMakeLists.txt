find_package(fmt REQUIRED)

add_library(cmake_cc_boilerplate_lib
    "../include/dummy.hh"
    dummy.cc)
add_library(cmake_cc_boilerplate::lib ALIAS cmake_cc_boilerplate_lib)
target_link_libraries(cmake_cc_boilerplate_lib
        PUBLIC fmt::fmt)
target_include_directories(cmake_cc_boilerplate_lib PUBLIC "${PROJECT_SOURCE_DIR}/include")

add_executable(cmake_cc_boilerplate_app "main.cc")
target_link_libraries(cmake_cc_boilerplate_app PRIVATE cmake_cc_boilerplate::lib)

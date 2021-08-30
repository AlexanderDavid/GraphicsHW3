find_package(fmt REQUIRED)
find_package (Eigen3 3.3 REQUIRED NO_MODULE)

add_library(hw1_lib
    "../include/Triangle.hh"
    Triangle.cc)
add_library(hw1::lib ALIAS hw1_lib)
target_link_libraries(hw1_lib
        PUBLIC fmt::fmt Eigen3::Eigen)
target_include_directories(hw1_lib PUBLIC "${PROJECT_SOURCE_DIR}/include")

add_executable(hw1_app "main.cc")
target_link_libraries(hw1_app PRIVATE hw1::lib)

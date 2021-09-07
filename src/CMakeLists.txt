find_package(fmt REQUIRED)
find_package(Eigen3 3.3 REQUIRED NO_MODULE)
find_package(OpenGL REQUIRED)
find_package(GLUT REQUIRED)


add_library(hw1_lib
    "../include/Triangle.hh"
    Triangle.cc
    "../include/Viewer.hh"
    Viewer.cc
    "../include/TriangleViewer.hh"
    TriangleViewer.cc
    "../include/Camera.hh"
    Camera.cc)
add_library(hw1::lib ALIAS hw1_lib)
target_link_libraries(hw1_lib PUBLIC
  Eigen3::Eigen
  ${OPENGL_LIBRARIES}
  ${GLUT_LIBRARY})

target_include_directories(hw1_lib PUBLIC
  "${PROJECT_SOURCE_DIR}/include"
  ${OPENGL_INCLUDE_DIRS}
  ${GLUT_INCLUDE_DIRS}
  "/usr/local/include/eigen3/unsupported/Eigen")


add_executable(hw1_app "main.cc")
target_link_libraries(hw1_app PRIVATE hw1::lib)

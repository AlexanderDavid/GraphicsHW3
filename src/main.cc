#include <GL/glut.h>

#include "TriangleViewer.hh"
#include "Triangle.hh"

#include <stdlib.h>
#include <iostream>
#include <memory>


auto main(int argc, char** argv) -> int
{
    srand48(209238434234);
    auto tv = viewer::TriangleViewer(argc, argv, 30, 0.523599);

    tv.go();

    return 0;
}

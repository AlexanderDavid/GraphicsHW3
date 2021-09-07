#include <GL/glut.h>

#include "TriangleViewer.hh"
#include "Triangle.hh"

#include <cstdlib>
#include <iostream>
#include <memory>


auto main(int argc, char** argv) -> int
{
    // Initialize the prng
    srand48(19581623);

    // Variables from the project handout
    constexpr auto numTriangles = 30;
    constexpr auto maxAngle     = 30 * M_PI / 180;

    // Initialize and start (blocking) the triangle viewer
    auto tv = viewer::TriangleViewer(argc, argv, numTriangles, maxAngle);
    tv.go();

    return 0;
}

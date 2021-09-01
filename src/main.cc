#include <GL/glut.h>

#include "TriangleViewer.hh"
#include "Triangle.hh"

#include <stdlib.h>
#include <iostream>


auto main(int argc, char** argv) -> int
{
    auto tv = triangleviewer::TriangleViewer(argc, argv);

    srand48(209238434234);

    auto triangles = triangle::Triangle::generateTriangles(30, 0.523599);

    for (int i = 0; i < triangles.size(); i++)
    {
        tv.add(triangles[i]);
    }

    tv.go();

    return 0;
}

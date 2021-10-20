#include <GL/glut.h>

#include "NGon.hh"
#include "NGonViewer.hh"

auto main(int argc, char** argv) -> int
{
    // Initialize and start (blocking) the triangle viewer
    auto nv = viewer::NGonViewer(argc, argv);
    nv.set(ngon::generateSymmetricNGon(500, 5, 5, {0, 1, 0}, {0, 0, 0}, 5));
    viewer::NGonViewer::go();

    return 0;
}

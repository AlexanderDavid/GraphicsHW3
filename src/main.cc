#include <GL/glut.h>

#include "NGon.hh"
#include "NGonViewer.hh"

auto main(int argc, char** argv) -> int
{
    // Initialize and start (blocking) the triangle viewer
    auto nv = viewer::NGonViewer(argc, argv);
    nv.set(ngon::generateSymmetricNGon(500, 1, 50, Eigen::Vector3d{ 1, 1, 0 }.normalized(), { 0, 0, 0 }, 5));
    viewer::NGonViewer::go();

    return 0;
}

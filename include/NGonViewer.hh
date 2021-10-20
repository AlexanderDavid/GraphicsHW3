#pragma once

#include "Viewer.hh"
#include "NGon.hh"
#include "Camera.hh"

namespace viewer
{
/**
 * A wrapper around the OpenGL wrapper that displays a series of triangles. Each triangle is
 * linked to the next along an edge. The angle between two touching triangles is also limited
 * based on a parameter
 */
class NGonViewer : public Viewer
{
public:
    /**
     * Create a TriangleViewer object that wraps around OpenGL to display triangles under
     * a series of constraints defined in the project handout
     *
     * @param argc Argument counter to pass to OpenGL
     * @param argv Argument list to pass to OpenGL
     * @param numTriangles Number of triangles to display
     * @param maxAngles Maximum angle between the normal of two touching triangles
     **/
    NGonViewer(int argc, char** argv);


    /**
     * Add a triangle to the scene
     *
     * @param triangle Triangle to add
     **/
    auto set(ngon::NGon ngon) -> void { ngon_ = std::move(ngon); };

private:
    /**
     * Class level openGL callbacks. These contain the actual callback code that will be called
     * by the static methods
     **/
    auto display() -> void override;
    auto resize(int width, int height) -> void override;
    auto motion(int x, int y) -> void override;
    auto mouse(int b, int state, int x, int y) -> void override;
    auto keyboard(unsigned char key, int x, int y) -> void override;

    /**
     * Print usage to stdout
     **/
    auto usage() const -> void;

    ngon::NGon ngon_;

    camera::Camera camera_;
};
}
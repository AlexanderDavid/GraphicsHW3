#ifndef TRIANGLE_VIEWER_HH
#define TRIANGLE_VIEWER_HH

#include "Viewer.hh"
#include "Triangle.hh"
#include "Camera.hh"

#include <GL/freeglut_std.h>
#include <memory>
#include <vector>

namespace viewer
{
    /**
     * A wrapper around the OpenGL wrapper that displays a series of triangles. Each triangle is
     * linked to the next along an edge. The angle between two touching triangles is also limited
     * based on a parameter
     */
    class TriangleViewer : public Viewer
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
        TriangleViewer(int argc, char** argv, size_t numTriangles, double maxAngle);


        /**
         * Add a triangle to the scene
         *
         * @param triangle Triangle to add
         **/
        auto add(const triangle::Triangle& triangle) -> void { triangles_.push_back(triangle); };

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

        size_t                          numTriangles_;
        double                          maxAngle_;
        int                             minMag_;
        int                             maxMag_;
        std::vector<triangle::Triangle> triangles_;

        camera::Camera camera_;
    };
}

#endif  // TRIANGLE_VIEWER_HH

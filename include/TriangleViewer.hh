/**
 * @file TriangleViewer.hh
 * @brief A wrapper around OpenGL to display a series of triangles
 **/

#ifndef TRIANGLE_VIEWER_HPP
#define TRIANGLE_VIEWER_HPP

#include "Viewer.hh"
#include "Triangle.hh"

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
        auto add(triangle::Triangle& triangle) -> void { triangles_.push_back(triangle); };

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
         * Compute the shift in the camera point of view that is induced by moving the mouse
         *
         * TODO: This should return a struct rather than changing the data members. Or change the
         *       function name
         *
         * @param dx Change in mouse X
         * @param dy Change in mouse Y
         * */
        auto computeCameraShift(int dx, int dy) -> void;

        size_t                          numTriangles_;
        double                          maxAngle_;
        std::vector<triangle::Triangle> triangles_;

        float camera_fov_;
        float camera_aspect_;
        float camera_near_;
        float camera_far_;

        float camera_eye_x_;
        float camera_eye_y_;
        float camera_eye_z_;

        float camera_view_x_;
        float camera_view_y_;
        float camera_view_z_;

        float camera_up_x_;
        float camera_up_y_;
        float camera_up_z_;

        float camera_right_x_;
        float camera_right_y_;
        float camera_right_z_;

        int   mouse_x_;
        int   mouse_y_;
        int   mouse_state_;
        float current_raster_pos_[4];
    };
}

#endif  // TRIANGLE_VIEWER_HPP

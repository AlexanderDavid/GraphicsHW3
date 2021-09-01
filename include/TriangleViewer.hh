#ifndef TRIANGLE_VIEWER_HPP
#define TRIANGLE_VIEWER_HPP

#include "Viewer.hh"
#include "Triangle.hh"

#include <GL/freeglut_std.h>
#include <memory>
#include <vector>

namespace triangleviewer
{
    class TriangleViewer : public std::enable_shared_from_this<TriangleViewer>
    {
    public:
        TriangleViewer(int argc, char** argv);


        static auto displayCb() -> void { instance_->display(); }
        static auto resizeCb(int width, int height) -> void { instance_->resize(width, height); }
        static auto motionCb(int x, int y) -> void { instance_->motion(x, y); }
        static auto mouseCb(int b, int state, int x, int y) -> void
        {
            instance_->mouse(b, state, x, y);
        }

        auto add(triangle::Triangle& triangle) -> void { triangles_.push_back(triangle); };

        auto go() -> void { vwr_.go(); }

    private:
        auto display() -> void;
        auto resize(int width, int height) -> void;
        auto motion(int x, int y) -> void;
        auto mouse(int b, int state, int x, int y) -> void;


        auto computeCameraShift(int dx, int dy) -> void;

        static viewer::Viewer  vwr_;
        static TriangleViewer* instance_;

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

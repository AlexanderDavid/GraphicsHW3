#include <GL/gl.h>
#include <GL/glut.h>
#include "Camera.hh"

namespace camera
{
    Camera::Camera()
    {
        // Initialize OpenGL viewport instance variables
        fov_          = 35.0;
        aspect_       = 1.0;
        near_         = 0.01;
        far_          = 100000.0;
        camera_eye_   = { 0, 0, -15 };
        camera_view_  = { 0, 0, 0 };
        camera_up_    = { 0, 1, 0 };
        camera_right_ = { 1, 0, 0 };

        mouse_       = { 0, 0 };
        mouse_state_ = 0;

        current_raster_pos_[0] = 0;
        current_raster_pos_[1] = 0;
        current_raster_pos_[2] = 0;
        current_raster_pos_[3] = 0;
    }
    auto Camera::display() -> void
    {
        gluPerspective(fov_, aspect_, near_, far_);
        gluLookAt(camera_eye_.x(),
                  camera_eye_.y(),
                  camera_eye_.z(),  // Camera eye point
                  camera_view_.x(),
                  camera_view_.y(),
                  camera_view_.z(),  // Camera view point
                  camera_up_.x(),
                  camera_up_.y(),
                  camera_up_.z()  // Camera up direction
        );
        glDepthRange(near_, far_);
    }

    auto Camera::motion(int x, int y) -> void
    {
        // Update the mouse position
        glGetFloatv(GL_CURRENT_RASTER_POSITION, current_raster_pos_);
        int   dx    = x - mouse_.x();
        int   dy    = y - mouse_.x();
        float pos_x = current_raster_pos_[0] + static_cast<float>(dx);
        float pos_y = current_raster_pos_[1] - static_cast<float>(dy);
        glRasterPos2f(pos_x, pos_y);

        // Compute the amount the camera should move (stolen from starter code)
        computeCameraShift(dx, dy);

        // Set the mouse position
        mouse_.x() = x;
        mouse_.x() = y;
    }

    auto Camera::mouse(int b, int state, int x, int y) -> void
    {
        // Update the mouse position
        mouse_.x()   = x;
        mouse_.y()   = y;
        mouse_state_ = state;
        glGetFloatv(GL_CURRENT_RASTER_POSITION, current_raster_pos_);
    }

    auto Camera::computeCameraShift(int dx, int dy) -> void
    {
        // Stolen from starter code
        // dx --> rotation around y axis
        // dy --> rotation about camera right axis
        float vvx    = camera_eye_.x() - camera_view_.x();
        float vvy    = camera_eye_.y() - camera_view_.y();
        float vvz    = camera_eye_.z() - camera_view_.z();
        float vvnorm = std::sqrt(vvx * vvx + vvy * vvy + vvz * vvz);
        vvx /= vvnorm;
        vvy /= vvnorm;
        vvz /= vvnorm;


        // Rotate around y axis
        // Rotate view direction
        float cosx        = std::cos(-dx * 0.006);
        float sinx        = std::sin(-dx * 0.006);
        float nvvx        = vvx * cosx + vvz * sinx;
        float nvvz        = -vvx * sinx + vvz * cosx;
        float nrightx     = camera_right_.x() * cosx + camera_right_.z() * sinx;
        float nrightz     = -camera_right_.x() * sinx + camera_right_.z() * cosx;
        vvx               = nvvx;
        vvz               = nvvz;
        camera_right_.x() = nrightx;
        camera_right_.z() = nrightz;

        // Rotate up direction
        float crossx   = camera_up_.z();
        float crossy   = 0.0;
        float crossz   = -camera_up_.z();
        float ydotup   = camera_up_.x();
        camera_up_.x() = camera_up_.x() * cosx + crossx * sinx;
        camera_up_.y() = camera_up_.y() * cosx + ydotup * (1.0 - cosx) + crossy * sinx;
        camera_up_.z() = camera_up_.z() * cosx + crossz * sinx;

        // Rotate right direction
        crossx            = camera_right_.z();
        crossy            = 0.0;
        crossz            = -camera_right_.x();
        ydotup            = camera_right_.y();
        camera_right_.x() = camera_right_.x() * cosx + crossx * sinx;
        camera_right_.y() = camera_right_.y() * cosx + ydotup * (1.0 - cosx) + crossy * sinx;
        camera_right_.z() = camera_right_.z() * cosx + crossz * sinx;

        // Rotate around camera-right axis
        // Rotate view direction
        cosx = std::cos(dy * 0.006);
        sinx = std::sin(dy * 0.006);
        float rightdotview
            = camera_right_.x() * vvx + camera_right_.y() * vvy + camera_right_.z() * vvz;
        crossx     = camera_right_.y() * vvz - camera_right_.z() * vvy;
        crossy     = camera_right_.z() * vvx - camera_right_.x() * vvz;
        crossz     = camera_right_.x() * vvy - camera_right_.y() * vvx;
        nvvx       = vvx * cosx + camera_right_.x() * rightdotview * (1.0 - cosx) + crossx * sinx;
        float nvvy = vvy * cosx + camera_right_.y() * rightdotview * (1.0 - cosx) + crossy * sinx;
        nvvz       = vvz * cosx + camera_right_.z() * rightdotview * (1.0 - cosx) + crossz * sinx;
        vvx        = nvvx;
        vvy        = nvvy;
        vvz        = nvvz;

        // Rotate up direction
        crossx         = camera_right_.y() * camera_up_.z() - camera_right_.z() * camera_up_.y();
        crossy         = camera_right_.z() * camera_up_.x() - camera_right_.x() * camera_up_.z();
        crossz         = camera_right_.x() * camera_up_.y() - camera_right_.y() * camera_up_.x();
        camera_up_.x() = camera_up_.x() * cosx + crossx * sinx;
        camera_up_.y() = camera_up_.y() * cosx + crossy * sinx;
        camera_up_.z() = camera_up_.z() * cosx + crossz * sinx;

        camera_eye_.x() = vvx * vvnorm + camera_view_.x();
        camera_eye_.y() = vvy * vvnorm + camera_view_.y();
        camera_eye_.z() = vvz * vvnorm + camera_view_.z();
    }

}

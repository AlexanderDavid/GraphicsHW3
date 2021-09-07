#include <GL/gl.h>
#include <GL/glut.h>
#include "Camera.hh"

namespace camera
{
    Camera::Camera()
    {
        // Initialize basic camera parameters
        fov_    = 35.0;
        aspect_ = 1.0;
        near_   = 0.01;
        far_    = 100000.0;

        // Initialize camera facing
        eye_   = { 0, 0, -15 };
        view_  = { 0, 0, 0 };
        up_    = { 0, 1, 0 };
        right_ = { 1, 0, 0 };

        // Initialize stateful variables for keyboard and mouse
        keystate_              = 0;
        current_raster_pos_[0] = 0;
        current_raster_pos_[1] = 0;
        current_raster_pos_[2] = 0;
        current_raster_pos_[3] = 0;
    }

    auto Camera::display() -> void
    {
        // Change camera to calculated paramters
        glLoadIdentity();
        gluPerspective(fov_, aspect_, near_, far_);
        gluLookAt(eye_.x(),
                  eye_.y(),
                  eye_.z(),  // Camera eye point
                  view_.x(),
                  view_.y(),
                  view_.z(),  // Camera view point
                  up_.x(),
                  up_.y(),
                  up_.z()  // Camera up direction
        );
        glEnable(GL_DEPTH_TEST);
        glDepthRange(near_, far_);
    }

    auto Camera::motion(int x, int y) -> void
    {
        // Update the mouse position
        glGetFloatv(GL_CURRENT_RASTER_POSITION, current_raster_pos_);
        int   dx    = x - mouse_.x;
        int   dy    = y - mouse_.y;
        float pos_x = current_raster_pos_[0] + static_cast<float>(dx);
        float pos_y = current_raster_pos_[1] - static_cast<float>(dy);
        glRasterPos2f(pos_x, pos_y);

        // Compute the shift
        computeCameraShift(dx, dy);

        // Update the mouse position
        mouse_.x = x;
        mouse_.y = y;
    }

    auto Camera::mouse(int b, int state, int x, int y) -> void
    {
        // Update the mouse position
        mouse_.x      = x;
        mouse_.y      = y;
        mouse_.state  = state;
        mouse_.button = b;
        keystate_     = glutGetModifiers();
        glGetFloatv(GL_CURRENT_RASTER_POSITION, current_raster_pos_);
    }

    auto Camera::computeCameraShift(int dx, int dy) -> void
    {
        // Stolen from starter code
        // dx --> rotation around y axis
        // dy --> rotation about camera right axis
        float vvx    = eye_.x() - view_.x();
        float vvy    = eye_.y() - view_.y();
        float vvz    = eye_.z() - view_.z();
        float vvnorm = std::sqrt(vvx * vvx + vvy * vvy + vvz * vvz);
        vvx /= vvnorm;
        vvy /= vvnorm;
        vvz /= vvnorm;

        // Rotate around y axis
        // Rotate view direction
        float cosx    = std::cos(-dx * 0.006);
        float sinx    = std::sin(-dx * 0.006);
        float nvvx    = vvx * cosx + vvz * sinx;
        float nvvz    = -vvx * sinx + vvz * cosx;
        float nrightx = right_.x() * cosx + right_.z() * sinx;
        float nrightz = -right_.x() * sinx + right_.z() * cosx;
        vvx           = nvvx;
        vvz           = nvvz;
        right_.x()    = nrightx;
        right_.z()    = nrightz;

        // Rotate up direction
        float crossx = up_.z();
        float crossy = 0.0;
        float crossz = -up_.x();
        float ydotup = up_.y();
        up_.x()      = up_.x() * cosx + crossx * sinx;
        up_.y()      = up_.y() * cosx + ydotup * (1.0 - cosx) + crossy * sinx;
        up_.z()      = up_.z() * cosx + crossz * sinx;

        // Rotate right direction
        crossx     = right_.z();
        crossy     = 0.0;
        crossz     = -right_.x();
        ydotup     = right_.y();
        right_.x() = right_.x() * cosx + crossx * sinx;
        right_.y() = right_.y() * cosx + ydotup * (1.0 - cosx) + crossy * sinx;
        right_.z() = right_.z() * cosx + crossz * sinx;

        // Rotate around camera-right axis
        // Rotate view direction
        cosx               = std::cos(dy * 0.006);
        sinx               = std::sin(dy * 0.006);
        float rightdotview = right_.x() * vvx + right_.y() * vvy + right_.z() * vvz;
        crossx             = right_.y() * vvz - right_.z() * vvy;
        crossy             = right_.z() * vvx - right_.x() * vvz;
        crossz             = right_.x() * vvy - right_.y() * vvx;
        nvvx               = vvx * cosx + right_.x() * rightdotview * (1.0 - cosx) + crossx * sinx;
        float nvvy         = vvy * cosx + right_.y() * rightdotview * (1.0 - cosx) + crossy * sinx;
        nvvz               = vvz * cosx + right_.z() * rightdotview * (1.0 - cosx) + crossz * sinx;
        vvx                = nvvx;
        vvy                = nvvy;
        vvz                = nvvz;

        // Rotate up direction
        crossx  = right_.y() * up_.z() - right_.z() * up_.y();
        crossy  = right_.z() * up_.x() - right_.x() * up_.z();
        crossz  = right_.x() * up_.y() - right_.y() * up_.x();
        up_.x() = up_.x() * cosx + crossx * sinx;
        up_.y() = up_.y() * cosx + crossy * sinx;
        up_.z() = up_.z() * cosx + crossz * sinx;

        eye_.x() = vvx * vvnorm + view_.x();
        eye_.y() = vvy * vvnorm + view_.y();
        eye_.z() = vvz * vvnorm + view_.z();
    }

}

#include <GL/gl.h>
#include <GL/glut.h>
#include "Camera.hh"

namespace camera
{
    Camera::Camera()
    {
        // Initialize OpenGL viewport instance variables
        fov_     = 35.0;
        aspect_  = 1.0;
        near_    = 0.01;
        far_     = 100000.0;
        eye_x_   = 0.0;
        eye_y_   = 0.0;
        eye_z_   = -15.0;
        view_x_  = 0.0;
        view_y_  = 0.0;
        view_z_  = 0.0;
        up_x_    = 0.0;
        up_y_    = 1.0;
        up_z_    = 0.0;
        right_x_ = 1.0;
        right_y_ = 0.0;
        right_z_ = 0.0;

        keystate_ = 0;

        current_raster_pos_[0] = 0;
        current_raster_pos_[1] = 0;
        current_raster_pos_[2] = 0;
        current_raster_pos_[3] = 0;
    }

    auto Camera::display() -> void
    {
        glLoadIdentity();
        gluPerspective(fov_, aspect_, near_, far_);
        gluLookAt(eye_x_,
                  eye_y_,
                  eye_z_,  // Camera eye point
                  view_x_,
                  view_y_,
                  view_z_,  // Camera view point
                  up_x_,
                  up_y_,
                  up_z_  // Camera up direction
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

        computeCameraShift(dx, dy);

        // Set the mouse position
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
        float vvx    = eye_x_ - view_x_;
        float vvy    = eye_y_ - view_y_;
        float vvz    = eye_z_ - view_z_;
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
        float nrightx = right_x_ * cosx + right_z_ * sinx;
        float nrightz = -right_x_ * sinx + right_z_ * cosx;
        vvx           = nvvx;
        vvz           = nvvz;
        right_x_      = nrightx;
        right_z_      = nrightz;

        // Rotate up direction
        float crossx = up_z_;
        float crossy = 0.0;
        float crossz = -up_x_;
        float ydotup = up_y_;
        up_x_        = up_x_ * cosx + crossx * sinx;
        up_y_        = up_y_ * cosx + ydotup * (1.0 - cosx) + crossy * sinx;
        up_z_        = up_z_ * cosx + crossz * sinx;

        // Rotate right direction
        crossx   = right_z_;
        crossy   = 0.0;
        crossz   = -right_x_;
        ydotup   = right_y_;
        right_x_ = right_x_ * cosx + crossx * sinx;
        right_y_ = right_y_ * cosx + ydotup * (1.0 - cosx) + crossy * sinx;
        right_z_ = right_z_ * cosx + crossz * sinx;

        // Rotate around camera-right axis
        // Rotate view direction
        cosx               = std::cos(dy * 0.006);
        sinx               = std::sin(dy * 0.006);
        float rightdotview = right_x_ * vvx + right_y_ * vvy + right_z_ * vvz;
        crossx             = right_y_ * vvz - right_z_ * vvy;
        crossy             = right_z_ * vvx - right_x_ * vvz;
        crossz             = right_x_ * vvy - right_y_ * vvx;
        nvvx               = vvx * cosx + right_x_ * rightdotview * (1.0 - cosx) + crossx * sinx;
        float nvvy         = vvy * cosx + right_y_ * rightdotview * (1.0 - cosx) + crossy * sinx;
        nvvz               = vvz * cosx + right_z_ * rightdotview * (1.0 - cosx) + crossz * sinx;
        vvx                = nvvx;
        vvy                = nvvy;
        vvz                = nvvz;

        // Rotate up direction
        crossx = right_y_ * up_z_ - right_z_ * up_y_;
        crossy = right_z_ * up_x_ - right_x_ * up_z_;
        crossz = right_x_ * up_y_ - right_y_ * up_x_;
        up_x_  = up_x_ * cosx + crossx * sinx;
        up_y_  = up_y_ * cosx + crossy * sinx;
        up_z_  = up_z_ * cosx + crossz * sinx;

        eye_x_ = vvx * vvnorm + view_x_;
        eye_y_ = vvy * vvnorm + view_y_;
        eye_z_ = vvz * vvnorm + view_z_;
    }

}

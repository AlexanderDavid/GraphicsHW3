#include "TriangleViewer.hh"

#include <GL/freeglut_std.h>
#include <GL/glut.h>
#include <GL/gl.h>

#include <algorithm>
#include <iostream>

namespace viewer
{
    TriangleViewer::TriangleViewer(int argc, char** argv, size_t numTriangles, double maxAngle)
    {
        instance_ = this;

        // Initialize OpenGL viewport instance variables
        camera_fov_     = 35.0;
        camera_aspect_  = 1.0;
        camera_near_    = 0.01;
        camera_far_     = 100000.0;
        camera_eye_x_   = 0.0;
        camera_eye_y_   = 0.0;
        camera_eye_z_   = -15.0;
        camera_view_x_  = 0.0;
        camera_view_y_  = 0.0;
        camera_view_z_  = 0.0;
        camera_up_x_    = 0.0;
        camera_up_y_    = 1.0;
        camera_up_z_    = 0.0;
        camera_right_x_ = 1.0;
        camera_right_y_ = 0.0;
        camera_right_z_ = 0.0;

        mouse_x_      = 0;
        mouse_y_      = 0;
        mouse_state_  = 0;
        mouse_button_ = 0;
        keystate_     = 0;

        current_raster_pos_[0] = 0;
        current_raster_pos_[1] = 0;
        current_raster_pos_[2] = 0;
        current_raster_pos_[3] = 0;

        // Set up the viewer
        setup(&argc, argv);

        // Initialize all of the triangles
        numTriangles_ = numTriangles;
        maxAngle_     = maxAngle;
        minMag_       = 1;
        maxMag_       = 2;
        if (argc == 1)
        {
            triangles_ = triangle::Triangle::generateTriangles(numTriangles, maxAngle);
        }
        else if (argc == 2)
        {
            triangles_ = triangle::Triangle::generateTriangles(std::string(argv[1]));
        }
    }

    auto TriangleViewer::display() -> void
    {
        // Clear the buffer
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        // Setup the camera
        glLoadIdentity();
        gluPerspective(camera_fov_, camera_aspect_, camera_near_, camera_far_);
        gluLookAt(camera_eye_x_,
                  camera_eye_y_,
                  camera_eye_z_,  // Camera eye point
                  camera_view_x_,
                  camera_view_y_,
                  camera_view_z_,  // Camera view point
                  camera_up_x_,
                  camera_up_y_,
                  camera_up_z_  // Camera up direction
        );
        glEnable(GL_DEPTH_TEST);
        glDepthRange(camera_near_, camera_far_);

        // Draw all of the objects in the scene
        for (auto& triangle : triangles_)
        {
            triangle.draw();
        }

        // Swap the buffer to display the image
        glutSwapBuffers();
        glutPostRedisplay();
    }

    auto TriangleViewer::resize(int width, int height) -> void
    {
        // Reshape the image
        glViewport(0, 0, width, height);
    }

    auto TriangleViewer::motion(int x, int y) -> void
    {
        // Update the mouse position
        glGetFloatv(GL_CURRENT_RASTER_POSITION, current_raster_pos_);
        int   dx    = x - mouse_x_;
        int   dy    = y - mouse_y_;
        float pos_x = current_raster_pos_[0] + static_cast<float>(dx);
        float pos_y = current_raster_pos_[1] - static_cast<float>(dy);
        glRasterPos2f(pos_x, pos_y);

        // Compute the amount the camera should move (stolen from starter code)
        if (mouse_button_ == GLUT_RIGHT_BUTTON && mouse_state_ == GLUT_DOWN)
        {
            camera_eye_x_ += static_cast<float>(dy);
            camera_eye_y_ += static_cast<float>(dy);
        }
        else if (mouse_button_ == GLUT_MIDDLE_BUTTON && mouse_state_ == GLUT_DOWN)
        {
            camera_view_x_ += static_cast<float>(dx) * 0.1f;
            camera_view_y_ += static_cast<float>(dy) * 0.1f;
        }
        else
        {
            computeCameraShift(dx, dy);
        }

        // Set the mouse position
        mouse_x_ = x;
        mouse_y_ = y;
    }

    auto TriangleViewer::mouse(int b, int state, int x, int y) -> void
    {
        // Update the mouse position
        mouse_x_      = x;
        mouse_y_      = y;
        mouse_state_  = state;
        mouse_button_ = b;
        keystate_     = glutGetModifiers();
        glGetFloatv(GL_CURRENT_RASTER_POSITION, current_raster_pos_);
    }

    auto TriangleViewer::keyboard(unsigned char key, int x, int y) -> void
    {
        // Define 90 degrees in radians
        constexpr double ninety = 90 * M_PI / 180;

        // Define variables for changing the triangle chain parameters
        double deltaAngle  = 0;
        int    deltaNumber = 0;

        switch (key)
        {
            case 'a':
                deltaAngle -= 0.05;
                break;
            case 'A':
                deltaAngle += 0.05;
                break;

            case 'b':
                deltaNumber -= 1;
                break;
            case 'B':
                deltaNumber += 1;
                break;

            default:
                break;
        }

        if (deltaAngle != 0)
        {
            // Clamp parameters to valid values and recalculate
            auto newAngle = std::clamp(maxAngle_ + deltaAngle, 0.005, ninety);
            if (newAngle != maxAngle_)
            {
                maxAngle_  = newAngle;
                triangles_ = triangle::Triangle::generateTriangles(numTriangles_, maxAngle_);
            }
        }
        else if (deltaNumber != 0)
        {
            if (deltaNumber == -1 && triangles_.size() > 1)
            {
                triangles_.pop_back();
            }
            else if (deltaNumber == 1)
            {
                triangles_.push_back(triangle::Triangle::generateTriangle(
                    triangles_.back(), maxAngle_, minMag_, maxMag_));
            }
        }

        std::cout << "Maximum Angle:       " << maxAngle_ << "\n"
                  << "Number of Triangles: " << triangles_.size() << "\n";
    }

    auto TriangleViewer::computeCameraShift(int dx, int dy) -> void
    {
        // Stolen from starter code
        // dx --> rotation around y axis
        // dy --> rotation about camera right axis
        float vvx    = camera_eye_x_ - camera_view_x_;
        float vvy    = camera_eye_y_ - camera_view_y_;
        float vvz    = camera_eye_z_ - camera_view_z_;
        float vvnorm = std::sqrt(vvx * vvx + vvy * vvy + vvz * vvz);
        vvx /= vvnorm;
        vvy /= vvnorm;
        vvz /= vvnorm;


        // Rotate around y axis
        // Rotate view direction
        float cosx      = std::cos(-dx * 0.006);
        float sinx      = std::sin(-dx * 0.006);
        float nvvx      = vvx * cosx + vvz * sinx;
        float nvvz      = -vvx * sinx + vvz * cosx;
        float nrightx   = camera_right_x_ * cosx + camera_right_z_ * sinx;
        float nrightz   = -camera_right_x_ * sinx + camera_right_z_ * cosx;
        vvx             = nvvx;
        vvz             = nvvz;
        camera_right_x_ = nrightx;
        camera_right_z_ = nrightz;

        // Rotate up direction
        float crossx = camera_up_z_;
        float crossy = 0.0;
        float crossz = -camera_up_x_;
        float ydotup = camera_up_y_;
        camera_up_x_ = camera_up_x_ * cosx + crossx * sinx;
        camera_up_y_ = camera_up_y_ * cosx + ydotup * (1.0 - cosx) + crossy * sinx;
        camera_up_z_ = camera_up_z_ * cosx + crossz * sinx;

        // Rotate right direction
        crossx          = camera_right_z_;
        crossy          = 0.0;
        crossz          = -camera_right_x_;
        ydotup          = camera_right_y_;
        camera_right_x_ = camera_right_x_ * cosx + crossx * sinx;
        camera_right_y_ = camera_right_y_ * cosx + ydotup * (1.0 - cosx) + crossy * sinx;
        camera_right_z_ = camera_right_z_ * cosx + crossz * sinx;

        // Rotate around camera-right axis
        // Rotate view direction
        cosx               = std::cos(dy * 0.006);
        sinx               = std::sin(dy * 0.006);
        float rightdotview = camera_right_x_ * vvx + camera_right_y_ * vvy + camera_right_z_ * vvz;
        crossx             = camera_right_y_ * vvz - camera_right_z_ * vvy;
        crossy             = camera_right_z_ * vvx - camera_right_x_ * vvz;
        crossz             = camera_right_x_ * vvy - camera_right_y_ * vvx;
        nvvx       = vvx * cosx + camera_right_x_ * rightdotview * (1.0 - cosx) + crossx * sinx;
        float nvvy = vvy * cosx + camera_right_y_ * rightdotview * (1.0 - cosx) + crossy * sinx;
        nvvz       = vvz * cosx + camera_right_z_ * rightdotview * (1.0 - cosx) + crossz * sinx;
        vvx        = nvvx;
        vvy        = nvvy;
        vvz        = nvvz;

        // Rotate up direction
        crossx       = camera_right_y_ * camera_up_z_ - camera_right_z_ * camera_up_y_;
        crossy       = camera_right_z_ * camera_up_x_ - camera_right_x_ * camera_up_z_;
        crossz       = camera_right_x_ * camera_up_y_ - camera_right_y_ * camera_up_x_;
        camera_up_x_ = camera_up_x_ * cosx + crossx * sinx;
        camera_up_y_ = camera_up_y_ * cosx + crossy * sinx;
        camera_up_z_ = camera_up_z_ * cosx + crossz * sinx;

        camera_eye_x_ = vvx * vvnorm + camera_view_x_;
        camera_eye_y_ = vvy * vvnorm + camera_view_y_;
        camera_eye_z_ = vvz * vvnorm + camera_view_z_;
    }

}

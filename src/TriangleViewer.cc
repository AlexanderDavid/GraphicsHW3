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

        camera_ = camera::Camera{};
        // Set up the viewer. Might make more sense to make TriangleViewer
        // a subclass of the Viewer...
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
        camera_.display();
        glEnable(GL_DEPTH_TEST);

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
        camera_.motion(x, y);
    }

    auto TriangleViewer::mouse(int b, int state, int x, int y) -> void
    {
        camera_.mouse(b, state, x, y);
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
}

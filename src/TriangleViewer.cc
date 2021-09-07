#include "TriangleViewer.hh"

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
        triangles_    = triangle::Triangle::generateTriangles(numTriangles, maxAngle);
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

        // Default to not recalculating the triangles unless one of the parameters is modified
        bool recalcAngles = false;
        bool recalcNumber = false;

        switch (key)
        {
            case 'a':
                maxAngle_ -= 0.05;
                recalcAngles = true;
                break;
            case 'A':
                maxAngle_ += 0.05;
                recalcAngles = true;
                break;

            case 'b':
                numTriangles_ -= 1;
                recalcNumber = true;
                break;
            case 'B':
                numTriangles_ += 1;
                recalcNumber = true;
                break;
        }

        if (recalcAngles)
        {
            // Clamp parameters to valid values and recalculate
            maxAngle_  = std::clamp(maxAngle_, 0.05, ninety);
            triangles_ = triangle::Triangle::generateTriangles(numTriangles_, maxAngle_);
        }
        else
        {
            // TODO: Do NOT recalculate all triangles like a bozo
            numTriangles_ = std::max(numTriangles_, 1ul);
            triangles_    = triangle::Triangle::generateTriangles(numTriangles_, maxAngle_);
        }
    }
}

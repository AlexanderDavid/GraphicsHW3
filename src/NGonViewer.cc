#include "NGonViewer.hh"

#include <GL/freeglut_std.h>
#include <GL/glut.h>
#include <GL/gl.h>

#include <algorithm>
#include <iostream>

namespace viewer
{
    NGonViewer::NGonViewer(int argc, char** argv)
    {
        instance_ = this;

        camera_ = camera::Camera{};
        // Set up the viewer. Might make more sense to make NGonViewer
        // a subclass of the Viewer...
        setup(&argc, argv);

        // Display the usage
        usage();
    }

    auto NGonViewer::display() -> void
    {
        // Clear the buffer
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        // Setup the camera
        glLoadIdentity();
        camera_.display();
        glEnable(GL_DEPTH_TEST);

        // Draw the object in the scene
        ngon_.display();

        // Swap the buffer to display the image
        glutSwapBuffers();
        glutPostRedisplay();
    }

    auto NGonViewer::resize(int width, int height) -> void
    {
        // Reshape the image
        glViewport(0, 0, width, height);
    }

    auto NGonViewer::motion(int x, int y) -> void { camera_.motion(x, y); }

    auto NGonViewer::mouse(int b, int state, int x, int y) -> void
    {
        camera_.mouse(b, state, x, y);
    }

    auto NGonViewer::keyboard(unsigned char key, int x, int y) -> void
    {
        switch (key)
        {
            case 'd':
            {
                ngon_.perturb(true);
                break;
            }
            case 'D':
            {
                ngon_.perturb(false);
                break;
            }
            default:
            {
                usage();
            }
        }

        std::cout << "NGon" << (ngon_.isPlanar() ? " is " : " is not ") << "planar\n";
        std::cout << "    " << (ngon_.isConvex() ? " is " : " is not ") << "convex\n";
    }

    auto NGonViewer::usage() const -> void
    {
        std::cout << "D - Perturb positive\n"
                  << "d - Perturb negative\n"
                  << "h - Print this usage\n";
        std::cout << "NGon" << (ngon_.isPlanar() ? " is " : " is not ") << "planar\n";
        std::cout << "    " << (ngon_.isConvex() ? " is " : " is not ") << "convex\n";
    }
}

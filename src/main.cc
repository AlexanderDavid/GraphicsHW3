#include <GL/glut.h>

#include "Triangle.hh"
#include "Viewer.hh"

void display()
{
    // called whenever the display needs to be redrawn

    glClear(GL_COLOR_BUFFER_BIT
            | GL_DEPTH_BUFFER_BIT);  // For 2D, usually leave out the depth buffer.

    glMatrixMode(GL_PROJECTION);  // Set up a simple orthographic projection, ignoring aspect ratio.
    glLoadIdentity();             //    TODO:  should almost certainly use a different projection!
    glOrtho(-1, 1, -1, 1, -2, 2);
    glMatrixMode(GL_MODELVIEW);

    glLoadIdentity();  // Start with no modeling transform.

    // TODO: INSERT DRAWING CODE HERE

    glutSwapBuffers();  // (Required for double-buffered drawing.)
                        // (For GLUT_SINGLE display mode, use glFlush() instead.)
}

void reshape(int w, int h)
{
    auto width  = w;  // Save width and height for possible use elsewhere.
    auto height = h;
    glViewport(0, 0, width, height);  // If you have a reshape function, you MUST call glViewport!
    // TODO: INSERT ANY OTHER CODE TO ACCOUNT FOR WINDOW SIZE (maybe set projection here).
    printf("Reshaped to width %d, height %d\n", width, height);
}

auto main(int argc, char** argv) -> int
{
    auto vwr = viewer::Viewer::getInstance(&argc, argv);
    vwr.setDisplayCallback(display);
    vwr.setReshapeCallback(reshape);

    glutMainLoop();

    return 0;
}

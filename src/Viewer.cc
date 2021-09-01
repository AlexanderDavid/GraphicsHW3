#include <GL/freeglut_std.h>
#include <GL/gl.h>
#include <mutex>

#include "Viewer.hh"

namespace viewer
{
    auto Viewer::setup(int* argc, char** argv, int width, int height) -> void
    {
        glutInit(argc, argv);
        glutInitDisplayMode(GLUT_DOUBLE | GLUT_DEPTH);
        glutInitWindowSize(width, height);
        glutInitWindowPosition(100, 100);
        glutCreateWindow("CPSC 6050");

        glClearColor(0.5, 0.5, 0.6, 0.0);
        glEnable(GL_DEPTH_TEST);

        glutDisplayFunc(&displayCb);
        glutReshapeFunc(&resizeCb);
        glutMotionFunc(&motionCb);
        glutMouseFunc(&mouseCb);
        glutKeyboardFunc(&keyboardCb);
    }

    Viewer* Viewer::instance_ = nullptr;
}

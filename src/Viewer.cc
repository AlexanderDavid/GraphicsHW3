#include <GL/freeglut_std.h>
#include <GL/gl.h>
#include <mutex>

#include "Viewer.hh"

namespace viewer
{
    auto Viewer::setup(int* argc, char** argv) -> void
    {
        glutInit(argc, argv);
        glutInitDisplayMode(GLUT_DOUBLE | GLUT_DEPTH);
        glutInitWindowSize(500, 500);
        glutInitWindowPosition(100, 100);
        glutCreateWindow("OpenGL Program");

        glClearColor(0.0, 0.0, 0.0, 1.0);
        glEnable(GL_DEPTH_TEST);
    }

    auto Viewer::setDisplayCallback(void (*fn)()) -> void { glutDisplayFunc(fn); }
    auto Viewer::setReshapeCallback(void (*fn)(int, int)) -> void { glutReshapeFunc(fn); }
    auto Viewer::setMotionCallback(void (*fn)(int, int)) -> void { glutMotionFunc(fn); };
    auto Viewer::setMouseCallback(void (*fn)(int, int, int, int)) -> void { glutMouseFunc(fn); }
}

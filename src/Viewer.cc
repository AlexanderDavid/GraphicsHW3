#include <GL/freeglut_std.h>
#include <GL/gl.h>
#include <GL/glut.h>

#include "Viewer.hh"

namespace viewer
{
    Viewer::Viewer(int* argc, char** argv)
    {
        glutInit(argc, argv);
        glutInitDisplayMode(GLUT_DOUBLE | GLUT_DEPTH);
        glutInitWindowSize(500, 500);
        glutInitWindowPosition(100, 100);
        glutCreateWindow("OpenGL Program");
    }

    auto Viewer::setDisplayCallback(void (*fn)()) -> void { glutDisplayFunc(fn); }
    auto Viewer::setReshapeCallback(void (*fn)(int, int)) -> void { glutReshapeFunc(fn); }
}

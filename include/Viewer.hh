#ifndef VIEWER_HPP
#define VIEWER_HPP

#include <functional>
#include <mutex>

#include <GL/glut.h>

namespace viewer
{
    class Viewer
    {
    public:
        static auto setup(int* argc, char** argv) -> void;

        static auto setDisplayCallback(void (*fn)()) -> void;
        static auto setReshapeCallback(void (*fn)(int, int)) -> void;
        static auto setMotionCallback(void (*fn)(int, int)) -> void;
        static auto setMouseCallback(void (*fn)(int, int, int, int)) -> void;

        static auto go() { glutMainLoop(); }

    private:
        static std::once_flag flag_;
    };
}

#endif  // VIEWER_HPP

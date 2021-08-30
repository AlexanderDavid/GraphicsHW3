#ifndef VIEWER_HPP
#define VIEWER_HPP

#include <functional>

namespace viewer
{
    class Viewer
    {
    public:
        static auto getInstance(int* argc, char** argv) -> Viewer&
        {
            static Viewer instance{ argc, argv };

            return instance;
        }

        auto setDisplayCallback(void (*fn)()) -> void;
        auto setReshapeCallback(void (*fn)(int, int)) -> void;

    private:
        Viewer(int* argc, char** argv);
    };
}

#endif  // VIEWER_HPP

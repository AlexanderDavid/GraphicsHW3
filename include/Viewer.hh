#ifndef VIEWER_HPP
#define VIEWER_HPP

#include <functional>
#include <mutex>

#include <GL/glut.h>

namespace viewer
{
    /**
     * Abstract base class for defining OpenGL applications
     **/
    class Viewer
    {
    public:
        /**
         * Construct the singleton instance of the viewer.
         * TODO: Make into an actual singleton
         **/
        Viewer();

        /**
         * Set up the OpenGL window and canvas
         *
         * @param argc Number of command line arguments
         * @param argv Command line arguments
         * @param width Width of the screen, Optional, default 500
         * @param height Height of the screen, Optional, default 500
         **/
        static auto setup(int* argc, char** argv, int width = 500, int height = 500) -> void;


        /**
         * Start the OpenGL main loop. Blocking.
         **/
        static auto go() -> void { glutMainLoop(); }

    protected:
        /**
         * Class level openGL callbacks. These contain the actual callback code that will be called
         * by the static methods
         **/
        virtual auto display() -> void                                 = 0;
        virtual auto resize(int width, int height) -> void             = 0;
        virtual auto motion(int x, int y) -> void                      = 0;
        virtual auto mouse(int b, int state, int x, int y) -> void     = 0;
        virtual auto keyboard(unsigned char key, int x, int y) -> void = 0;


        static Viewer* instance_;

    private:
        /**
         * Static method callbacks using the singleton of the viewer for OpenGL
         **/
        static auto displayCb() -> void { instance_->display(); }
        static auto resizeCb(int width, int height) -> void { instance_->resize(width, height); }
        static auto motionCb(int x, int y) -> void { instance_->motion(x, y); }
        static auto mouseCb(int b, int state, int x, int y) -> void
        {
            instance_->mouse(b, state, x, y);
        }
    };
}

#endif  // VIEWER_HPP

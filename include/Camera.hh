#ifndef CAMERA_HH
#define CAMREA_HH

#include <Eigen/Dense>
#include <Eigen/src/Core/Matrix.h>

namespace camera
{
    struct Mouse
    {
        int x      = 0;
        int y      = 0;
        int state  = 0;
        int button = 0;
    };

    class Camera
    {
    public:
        Camera();

        /**
         * OpenGL Callbacks
         **/
        auto display() -> void;
        auto motion(int x, int y) -> void;
        auto mouse(int b, int state, int x, int y) -> void;

    private:
        /**
         * Compute the shift in the camera point of view that is induced by moving the mouse
         *
         * TODO: This should return a struct rather than changing the data members. Or change the
         *       function name
         *
         * @param dx Change in mouse X
         * @param dy Change in mouse Y
         * */
        auto computeCameraShift(int dx, int dy) -> void;

        float fov_;
        float aspect_;
        float near_;
        float far_;

        Eigen::Vector3f eye_;
        Eigen::Vector3f view_;
        Eigen::Vector3f up_;
        Eigen::Vector3f right_;

        Mouse mouse_;
        int   keystate_;
        float current_raster_pos_[4];
    };


}

#endif  // CAMERA_HH

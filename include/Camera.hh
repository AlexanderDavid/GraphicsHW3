#ifndef CAMERA_HH
#define CAMREA_HH

#include <Eigen/Dense>

namespace camera
{
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

        Eigen::Vector3f camera_eye_;
        Eigen::Vector3f camera_view_;
        Eigen::Vector3f camera_up_;
        Eigen::Vector3f camera_right_;

        Eigen::Vector2i mouse_;
        int mouse_state_;
        float current_raster_pos_[4];
    };

}

#endif  // CAMERA_HH

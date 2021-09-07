#ifndef CAMERA_HH
#define CAMREA_HH

#include <Eigen/Dense>

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

        float camera_fov_;
        float camera_aspect_;
        float camera_near_;
        float camera_far_;

        float camera_eye_x_;
        float camera_eye_y_;
        float camera_eye_z_;

        float camera_view_x_;
        float camera_view_y_;
        float camera_view_z_;

        float camera_up_x_;
        float camera_up_y_;
        float camera_up_z_;

        float camera_right_x_;
        float camera_right_y_;
        float camera_right_z_;

        Mouse mouse_;
        int   mouse_x_;
        int   mouse_y_;
        int   mouse_state_;
        int   mouse_button_;
        int   keystate_;
        float current_raster_pos_[4];
    };


}

#endif  // CAMERA_HH

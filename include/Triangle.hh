#ifndef TRIANGLE_HPP
#define TRIANGLE_HPP

#include <tuple>

#include <Eigen/Dense>

namespace triangle
{
    using Point  = Eigen::Vector3d;
    using Vector = Eigen::Vector3d;
    using Color  = Eigen::Vector3d;

    class Triangle
    {
    public:
        /**
         * Construct a Triangle
         *
         * @param point1 First point of the triangle
         * @param point2 Second point of the triangle
         * @param point3 Third point of the triangle
         * @param color Color of the triangle
         **/
        Triangle(const Point& point1, const Point& point2, const Point& point3, const Color& color);

        /**
         * Get the area of the given triangle
         *
         * @returns Area of triangle
         **/
        [[nodiscard]] auto area() const -> const double;

        /**
         * Get the normalized unit vector of the triangle
         *
         * @returns Normal vector with magnatude of 1
         **/
        [[nodiscard]] auto unitNormal() const -> const Vector;

        /**
         * Get the edge vectors of the triangle
         *
         * @returns triangle edge vectors in cannonical order
         **/
        [[nodiscard]] auto edgeVectors() const -> const std::tuple<Vector, Vector, Vector>;

        /**
         * Get the points of the triangle
         *
         * @returns triangle points in cannonical order
         **/
        [[nodiscard]] auto points() const -> const std::tuple<Point, Point, Point>;

        /**
         * Get the aspect ratio of the triangle
         *
         * @returns aspect ratio of triangle
         **/
        [[nodiscard]] auto aspectRatio() const -> const std::pair<double, double>;

        /**
         * Draw the triangle using OpenGL
         **/
        auto draw() const -> const void;

        /**
         * Generate triangles according to the project handout
         *
         * @param numTriangles Number of triangles to generate
         * @param maximumAngles Maximum angle between the normal vectors of two
         *                      touching triangles
         *
         * @returns List of valid triangles
         * */
        static auto generateTriangles(size_t numTriangles, double maximumAngle)
            -> std::vector<Triangle>;

    private:
        Point point1_;
        Point point2_;
        Point point3_;
        Color color_;
    };

}

#endif  // TRIANGLE_HPP

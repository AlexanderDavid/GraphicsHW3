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
        Triangle(const Point& point1, const Point& point2, const Point& point3, const Color& color);

        auto area() -> const double;
        auto unitNormal() -> const Vector;
        auto edgeVectors() -> const std::tuple<Vector, Vector, Vector>;
        auto aspectRatio() -> const std::pair<double, double>;

        auto draw() -> void;

    private:
        Point point1_;
        Point point2_;
        Point point3_;
        Color color_;
    };

}

#endif  // TRIANGLE_HPP

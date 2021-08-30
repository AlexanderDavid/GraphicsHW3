#include "Triangle.hh"

#include <Eigen/OpenGLSupport>
namespace triangle
{
    Triangle::Triangle(const Point& point1,
                       const Point& point2,
                       const Point& point3,
                       const Color& color)
    {
        point1_ = point1;
        point2_ = point2;
        point3_ = point3;
        color_  = color;
    }

    auto Triangle::area() -> const double
    {
        auto edge1 = point2_ - point1_;
        auto edge2 = point3_ - point1_;

        return 0.5 * edge1.cross(edge2).norm();
    }

    auto Triangle::unitNormal() -> const Vector
    {
        auto edge1 = point2_ - point1_;
        auto edge2 = point3_ - point1_;

        return edge2.cross(edge1) / edge2.cross(edge1).norm();
    }

    auto Triangle::edgeVectors() -> const std::tuple<Vector, Vector, Vector>
    {
        return { point2_ - point1_, point3_ - point1_, point3_ - point2_ };
    }

    auto Triangle::aspectRatio() -> const std::pair<double, double>
    {
        auto edge1Length = (point2_ - point1_).norm();
        auto edge2Length = (point3_ - point1_).norm();
        auto edge3Length = (point3_ - point2_).norm();

        return { std::max({ edge1Length, edge2Length, edge3Length }),
                 std::min({ edge1Length, edge2Length, edge3Length }) };
    }

    auto Triangle::draw() -> void {}
}

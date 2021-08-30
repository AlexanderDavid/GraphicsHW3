#include "Triangle.hh"

namespace triangle
{
    Triangle::Triangle(const Point& point1, const Point& point2, const Point& point3)
    {
        point1_ = std::move(point1);
        point2_ = std::move(point2);
        point3_ = std::move(point3);
    }

    const double Triangle::area()
    {
        auto AB = point1_ - point2_;
        auto AC = point1_ - point3_;
        auto angle = std::atan2(AB.cross(AC).norm(), AB.dot(AC));

        // https://math.stackexchange.com/questions/128991/how-to-calculate-the-area-of-a-3d-triangle
        return 0.5 * AB.norm() * AC.norm() * std::sin(angle);
    }

    const Vector Triangle::unitNormal() { return {}; }

    const std::tuple<Vector, Vector, Vector> Triangle::edgeVectors() { return {}; }

    const std::pair<double, double> Triangle::aspectRatio() { return {}; }
}

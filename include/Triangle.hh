#ifndef TRIANGLE_HPP
#define TRIANGLE_HPP

#include <tuple>

#include <Eigen/Dense>

namespace triangle
{
    using Point  = Eigen::Vector3d;
    using Vector = Eigen::Vector3d;

    class Triangle
    {
    public:
        Triangle(const Point& point1, const Point& point2, const Point& point3);

        const double                             area();
        const Vector                             unitNormal();
        const std::tuple<Vector, Vector, Vector> edgeVectors();
        const std::pair<double, double>          aspectRatio();

    private:
        Point point1_;
        Point point2_;
        Point point3_;
    };

}

#endif  // TRIANGLE_HPP

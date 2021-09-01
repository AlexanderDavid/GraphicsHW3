#include <GL/gl.h>

#include "Triangle.hh"

#include <iostream>
#include <stdlib.h>

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

    auto Triangle::area() const -> const double
    {
        auto edge1 = point2_ - point1_;
        auto edge2 = point3_ - point1_;

        return 0.5 * edge1.cross(edge2).norm();
    }

    auto Triangle::unitNormal() const -> const Vector
    {
        auto edge1 = point2_ - point1_;
        auto edge2 = point3_ - point1_;

        return edge2.cross(edge1) / edge2.cross(edge1).norm();
    }

    auto Triangle::edgeVectors() const -> const std::tuple<Vector, Vector, Vector>
    {
        return { point2_ - point1_, point3_ - point1_, point3_ - point2_ };
    }

    auto Triangle::points() const -> const std::tuple<Point, Point, Point>
    {
        return { point1_, point2_, point3_ };
    }

    auto Triangle::aspectRatio() const -> const std::pair<double, double>
    {
        auto edge1Length = (point2_ - point1_).norm();
        auto edge2Length = (point3_ - point1_).norm();
        auto edge3Length = (point3_ - point2_).norm();

        return { std::max({ edge1Length, edge2Length, edge3Length }),
                 std::min({ edge1Length, edge2Length, edge3Length }) };
    }

    auto Triangle::draw() const -> const void
    {
        glBegin(GL_TRIANGLES);

        glColor3d(color_.x(), color_.y(), color_.z());
        glVertex3d(point1_.x(), point1_.y(), point1_.z());
        glVertex3d(point2_.x(), point2_.y(), point2_.z());
        glVertex3d(point3_.x(), point3_.y(), point3_.z());

        glEnd();
    }

    auto Triangle::generateTriangles(size_t numTriangles, double maximumAngle)
        -> std::vector<Triangle>
    {
        std::vector<Triangle> triangles{};
        triangle::Triangle    triangle{
            { 0, 0, 0 }, { 0, 1.5, 0 }, { 0, 0.5, 0 }, { drand48(), drand48(), drand48() }
        };

        triangles.push_back(triangle);

        auto [point1, point2, point3] = triangle.points();
        auto [edge1, edge2, edge3] = triangle.edgeVectors();

        for (size_t i = 0; i < numTriangles; i++)
        {
            while (true)
            {
                Vector             randomVector{ drand48() * 3, drand48() * 3, drand48() * 3 };
                std::vector<Vector> vectors = { point1, point2, point3 };
                std::random_shuffle(vectors.begin(), vectors.end());

                triangle::Triangle newTriangle{
                    vectors[0] + randomVector,
                    vectors[1],
                    vectors[2],
                    { drand48(), drand48(), drand48() }
                };

                auto [edge1, edge2, edge3] = newTriangle.edgeVectors();

                if (0 > std::acos(newTriangle.unitNormal().dot(triangle.unitNormal()))
                    > maximumAngle)
                    continue;
                std::cout << "valid angles\n";

                if (std::abs(edge1.norm()) > 2 || std::abs(edge1.norm()) < 1
                    || std::abs(edge2.norm()) > 2 || std::abs(edge2.norm()) < 1
                    || std::abs(edge3.norm()) > 2 || std::abs(edge3.norm()) < 1)
                    continue;



                point1 = newTriangle.point1_;
                point2 = newTriangle.point2_;
                point3 = newTriangle.point3_;

                std::cout << edge1 << " | " << edge2 << " | " << edge3 << "\n";
                triangles.push_back(newTriangle);
                break;
            }
        }


        return triangles;
    }
}

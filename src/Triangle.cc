#include <GL/gl.h>

#include "Triangle.hh"

#include <cmath>
#include <fstream>
#include <iostream>
#include <sstream>
#include <random>
#include <cstdlib>

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

    auto Triangle::generateTriangles(std::string stlFile) -> std::vector<Triangle>
    {
        std::string   line;
        std::ifstream file{ stlFile };

        if (!file.is_open())
        {
            std::cerr << "Couldn't open stl file: " << stlFile;
            return {};
        }

        std::vector<Triangle> triangles{};
        std::vector<Point>    points{};
        int                   i = 0;
        while (getline(file, line))
        {
            if (points.size() == 3)
            {
                Color color{ drand48(), drand48(), drand48() };
                triangles.emplace_back(points[0], points[1], points[2], color);
                points.clear();
            }

            if (line.find("   vertex") == 0)
            {
                auto               tokens = line.substr(10);
                std::stringstream  ss(tokens);
                std::string        buf;
                std::vector<float> coords{};
                while (ss >> buf)
                {
                    coords.push_back(std::stof(buf));
                }
                points.emplace_back(coords[0], coords[1], coords[2]);
            }
        }

        std::cout << triangles.size() << " triangles loaded\n";
        return triangles;
    }

    auto Triangle::generateTriangles(size_t numTriangles,
                                     double maximumAngle,
                                     int    minMag,
                                     int    maxMag) -> std::vector<Triangle>
    {
        // Define a vector to store valid triangles
        std::vector<Triangle> triangles{};

        // Define a base triangle that is valid.
        triangle::Triangle triangle{
            { 0, 0, 0 }, { 0, 0, 1.001 }, { 0, 1.001, 0 }, { drand48(), drand48(), drand48() }
        };
        triangles.push_back(triangle);

        // Remember its' points for the next triangle
        auto [point1, point2, point3] = triangle.points();

        // Generate numTriangles valid triangles
        for (size_t i = 0; i < numTriangles; i++)
        {
            // Loop until a valid triangle is found
            while (true)
            {
                auto newTriangle = generateTriangle(triangles.back(), maximumAngle, minMag, maxMag);

                // Add the triangle to the list and break out of the infinite validity check
                triangles.push_back(newTriangle);
                break;
            }
        }


        return triangles;
    }


    auto Triangle::generateTriangle(const Triangle& triangle,
                                    double          maximumAngle,
                                    int             minMag,
                                    int             maxMag) -> Triangle
    {
        // Loop until a valid triangle is found
        while (true)
        {
            // Define a random vector that will be added to a randomly chosen point
            Vector randomVector{ drand48() * 3, drand48() * 3, drand48() * 3 };

            // Shuffle the points of the old triangle
            std::vector<Vector> points = { triangle.point1_, triangle.point2_, triangle.point3_ };
            std::shuffle(points.begin(), points.end(), std::mt19937(std::random_device()()));

            // Define a new triangle that shares two random points with the old triangle but
            // has its' third point randomly perturbed from the last point of the old triangle
            triangle::Triangle newTriangle{
                points[0] + randomVector, points[1], points[2], { drand48(), drand48(), drand48() }
            };

            // Check that the angle is within acceptable ranges
            auto angle = std::acos(newTriangle.unitNormal().dot(triangle.unitNormal()));
            if (std::isnan(angle) || -maximumAngle > angle || angle > maximumAngle)
                continue;

            // Check that the magnitude of any of the edges is not outside the specified range
            auto [edge1, edge2, edge3] = newTriangle.edgeVectors();
            if (std::abs(edge1.norm()) > maxMag || std::abs(edge1.norm()) < minMag
                || std::abs(edge2.norm()) > maxMag || std::abs(edge2.norm()) < minMag
                || std::abs(edge3.norm()) > maxMag || std::abs(edge3.norm()) < minMag)
                continue;

            return newTriangle;
        }
    }
}

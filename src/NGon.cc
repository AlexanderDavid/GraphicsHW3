#include <random>
#include <GL/gl.h>
#include <iostream>
#include "NGon.hh"
#include "Face.hh"

namespace ngon
{
    /**
     * Return the index of a given element in a vector, adding it if it is not
     * already present
     * @tparam T Type of the objects inside the vector
     * @param vec Vector to search in
     * @param el Element to add
     * @return Position of the element in vector
     */
    template<class T>
    auto tryAdd(std::vector<T>& vec, T el) -> size_t
    {
        // Try to find el in vec
        auto idx = std::find(vec.begin(), vec.end(), el);

        // If found return index
        if (idx != vec.end())
            return idx - vec.begin();

        // Else add it to the end and return the index
        vec.push_back(el);
        return vec.size() - 1;
    }

    auto randomDouble() -> double
    {
        static std::uniform_real_distribution<double> dist(0.0, 1.0);
        static std::mt19937                           gen(123);

        return dist(gen);
    }
    auto randomUnitVector() -> Eigen::Vector3d
    {
        Eigen::Vector3d vec{ randomDouble(), randomDouble(), randomDouble() };
        return vec.normalized();
    }

    auto NGon::addFace(const std::vector<Eigen::Vector3d>& vertices,
                       const std::vector<Eigen::Vector3d>& normals,
                       const std::vector<Eigen::Vector2d>& textureCoords) -> void
    {
        std::vector<size_t> vertexIdxs, normalIdxs, textureCoordIdxs;

        for (const auto& vertex : vertices)
            vertexIdxs.push_back(tryAdd(vertices_, vertex));

        for (const auto& normal : normals)
            normalIdxs.push_back(tryAdd(normals_, normal));

        for (const auto& textureCoord : textureCoords)
            textureCoordIdxs.push_back(tryAdd(textureCoords_, textureCoord));

        faces_.emplace_back(vertexIdxs, normalIdxs, textureCoordIdxs);
    }
    auto NGon::size() const noexcept -> size_t { return faces_.size(); }

    auto NGon::display() const -> void
    {
        for (auto face : faces_)
        {
            std::cout << textureCoords_.size() << "\n";
            glBegin(GL_POLYGON);
            for (int i = 0; i < face.size(); i++)
            {
                //            glColor3d(0.51, 0.81, 0.51);
                auto [vi, ni, ti] = face.getVertex(i);
                auto color = generateColor(textureCoords_[ti % textureCoords_.size()]);
                glColor3d(color.x(), color.y(), color.z());
                glVertex3d(vertices_[vi].x(), vertices_[vi].y(), vertices_[vi].z());
            }
            glEnd();
        }
    }
    auto NGon::perturb(bool inPositive) -> void
    {
        // Keep track of the sum of all normals for each vertex
        Eigen::Vector3d perturbAmt[vertices_.size()];

        for (const auto& face : faces_)
        {
            for (int i = 0; i < face.size(); i++)
            {
                auto [vi, ni, ti] = face.getVertex(i);

                perturbAmt[vi] += normals_[ni];
            }
        }

        // Perturb by the normalized pertub amount
        for (int i = 0; i < vertices_.size(); i++)
        {
            vertices_[i] = vertices_[i] + perturbAmt[i].normalized() * (inPositive ? 0.01 : -0.01);
        }
    }

    auto generateSymmetricNGon(size_t                 numSides,
                               size_t                 numNormals,
                               size_t                 numTextureCoords,
                               const Eigen::Vector3d& normal,
                               const Eigen::Vector3d& center,
                               const float            radius) -> NGon
    {
        assert(numSides > 4);

        // Generate normals randomly
        std::vector<Eigen::Vector3d> normals;
        for (size_t i = 0; i < numNormals; i++)
            normals.push_back(randomUnitVector());

        // Generate texture coords randomly
        std::vector<Eigen::Vector2d> textures;
        for (size_t i = 0; i < numTextureCoords; i++)
            textures.emplace_back(randomDouble(), randomDouble());

        // Generate the faces
        NGon            ngon;
        double          t = 2 * M_PI / static_cast<double>(numSides);
        Eigen::Vector3d origin{ radius, 0, 0 };

        std::vector<Eigen::Vector3d> faceVertices{};
        faceVertices.emplace_back(radius, 0, 0);
        std::vector<Eigen::Vector3d> faceNormals{};
        std::vector<Eigen::Vector2d> faceTextures{};


        for (int i = 1; i < numSides; i++)
        {
            auto x = radius * std::cos(t * i);
            auto y = radius * std::sin(t * i);
            // auto x_ = radius * std::cos(t * (i + 1));
            // auto y_ = radius * std::sin(t * (i + 1));
            auto z = 0;

            faceVertices.emplace_back(x, y, z);

            // std::vector<Eigen::Vector3d> faceVerticies{ { x, y, z }, { x_, y_, z }, origin };

            // std::vector<Eigen::Vector3d> faceNormals;
            // for (int j = 0; j < 3; j++)
            faceNormals.push_back(
                normals[std::floor(randomDouble() * static_cast<int>(normals.size()))]);

            // std::vector<Eigen::Vector2d> faceTextures;
            // for (int j = 0; j < 3; j++)
            faceTextures.emplace_back(
                textures[std::floor(randomDouble() * static_cast<int>(textures.size()))]);
        }

        ngon.addFace(faceVertices, faceNormals, faceTextures);

        return ngon;
    }

    auto generateColor(Eigen::Vector2d texCoords) -> Eigen::Vector3d
    {
        auto ss    = std::pow(texCoords.x(), 2);
        auto tt    = std::pow(texCoords.y(), 2);
        auto smt   = std::pow(texCoords.x() - texCoords.y(), 2);
        auto denom = 3.0 / (ss + tt + smt + 1e-9);

        return { ss * denom, tt * denom, smt * denom };
    }

}

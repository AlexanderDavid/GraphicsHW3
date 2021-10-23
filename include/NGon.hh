#pragma once

#include "Face.hh"

#include <vector>

#include "Eigen/Dense"

namespace ngon
{
    class NGon
    {
    public:
        NGon() = default;

        auto addFace(const std::vector<Eigen::Vector3d>& vertices,
                     const std::vector<Eigen::Vector3d>& normals,
                     const std::vector<Eigen::Vector2d>& textureCoords) -> void;

        auto display() const -> void;

        auto perturb(bool inPositive) -> void;

        [[nodiscard]] inline auto size() const noexcept -> size_t;

        [[nodiscard]] auto isPlanar() const -> bool;

        [[nodiscard]] auto isConvex() const -> bool;

    private:
        std::vector<Eigen::Vector3d> vertices_{};
        std::vector<Eigen::Vector3d> normals_{};
        std::vector<Eigen::Vector2d> textureCoords_{};

        std::vector<Face> faces_;
    };


    auto generateSymmetricNGon(size_t                 numSides,
                               size_t                 numNormals,
                               size_t                 numTextureCoords,
                               const Eigen::Vector3d& normal,
                               const Eigen::Vector3d& center,
                               const float            radius) -> NGon;

    auto generateColor(Eigen::Vector2d texCoords) -> Eigen::Vector3d;

}

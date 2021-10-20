#pragma once

#include <tuple>
#include <vector>
#include <assert.h>

namespace ngon
{

class Face
{
public:
    Face() = default;

    Face(std::vector<std::size_t> vertexIdxs, std::vector<std::size_t> normalIdxs, std::vector<std::size_t> textureCoordIdxs) :
        vertexIdxs_(std::move(vertexIdxs)),
        normalIdxs_(std::move(normalIdxs)),
        textureCoordIdxs_(std::move(textureCoordIdxs)) { }

    auto addVertex(std::size_t vertexIdx, std::size_t normalIdx, std::size_t textureCoordIdx) -> void
    {
        vertexIdxs_.push_back(vertexIdx);
        normalIdxs_.push_back(normalIdx);
        textureCoordIdxs_.push_back(textureCoordIdx);
    }

    auto getVertex(std::size_t idx) const -> std::tuple<std::size_t, std::size_t, std::size_t>
    {
        assert(idx < vertexIdxs_.size());

        return std::make_tuple(vertexIdxs_[idx], normalIdxs_[idx], textureCoordIdxs_[idx]);
    }

    [[nodiscard]] auto size() const -> std::size_t { return vertexIdxs_.size(); }

private:
    std::vector<std::size_t> vertexIdxs_;
    std::vector<std::size_t> normalIdxs_;
    std::vector<std::size_t> textureCoordIdxs_;
};

}

/**
 * building-blocks v1.0
 *
 * @author mkhan3189
 * http://www.icplusplus.com
 * https://www.github.com/mkhan3189/building-blocks
 * https://www.github.com/mkhan3189/building-blocks-engine
 *
 * This program is free software: you can redistribute it and/or modify it under the terms of the
 * GNU General Public License as published by the Free Software Foundation, version 3 of the License.
 */

#include "engine/internal/line.hh"
#include "engine/internal/block.hh"
#include "engine/internal/player.hh"

namespace buildingblocks {

namespace engine {

namespace internal {

Block::Block(const buildingblocks::engine::internal::Line *const vertex1,
             const buildingblocks::engine::internal::Line *const vertex2,
             const buildingblocks::engine::internal::Line* const vertex3,
             const buildingblocks::engine::internal::Line* const vertex4,
             buildingblocks::engine::internal::Player* owner_)
{
    vertices_[0] = vertex1;
    vertices_[1] = vertex2;
    vertices_[2] = vertex3;
    vertices_[3] = vertex4;
    this->owner_ = owner_;
}

Block::~Block()
{
}

bool Block::operator==(const Block &other) const
{
    return vertices_[0] == other.vertices_[0] && vertices_[1] == other.vertices_[1]
            && vertices_[2] == other.vertices_[2] && vertices_[3] == other.vertices_[3];
}

const buildingblocks::engine::internal::Line** Block::getVertices(void)
{
    return vertices_;
}

const buildingblocks::engine::internal::Player* Block::owner(void) const
{
    return owner_;
}

void Block::setOwner(buildingblocks::engine::internal::Player *owner_)
{
    this->owner_ = owner_;
}

} // namespace internal
} // namespace engine
} // namespace buildingblocks

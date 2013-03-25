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

#ifndef BUILDING_BLOCKS_ENGINE_BLOCK_HH
#define BUILDING_BLOCKS_ENGINE_BLOCK_HH

#include "engine/internal/line.hh"

namespace buildingblocks {

namespace engine {

namespace internal {

class Line;
class Player;

class Block
{
public:
    static const int kMaxLines = 4;

    explicit Block(const buildingblocks::engine::internal::Line *const vertex1,
                   const buildingblocks::engine::internal::Line *const vertex2,
                   const buildingblocks::engine::internal::Line* const vertex3,
                   const buildingblocks::engine::internal::Line* const vertex4,
                   buildingblocks::engine::internal::Player *owner);
    virtual ~Block(void);
    bool operator==(const Block& other) const;

    const buildingblocks::engine::internal::Line** getVertices(void);
    const buildingblocks::engine::internal::Player* owner(void) const;
    void setOwner(buildingblocks::engine::internal::Player* owner_);
private:
    const buildingblocks::engine::internal::Line* vertices_[kMaxLines];
    buildingblocks::engine::internal::Player* owner_;
};

class BlockPredicate {
    explicit BlockPredicate(const Block& block_) :
        block_(block_){
    }
    bool operator()(Block* inBlock_) {
        return *inBlock_ == block_;
    }

private:
    Block block_;
};

} // namespace internal
} // namespace engine
} // namespace buildingblocks
#endif // BUILDING_BLOCKS_ENGINE_Block_HH

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

#ifndef BUILDING_BLOCKS_ENGINE_HH
#define BUILDING_BLOCKS_ENGINE_HH

#include <vector>

namespace buildingblocks {

namespace engine {

namespace internal {

class Board;

}
class Engine
{
public:
    explicit Engine(int argc, const char **argv);
    virtual ~Engine(void);
    void setBoard(buildingblocks::engine::internal::Board* board_);
    buildingblocks::engine::internal::Board* board(void) const;
protected:

private:

   buildingblocks::engine::internal::Board* board_;
};

} // namespace engine
} // namespace buildingblocks
#endif // BUILDING_BLOCKS_ENGINE_HH

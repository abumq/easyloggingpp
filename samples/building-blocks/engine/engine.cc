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

#include "engine.hh"
#include "easylogging++.h"
#include "engine/internal/board.hh"
#include "engine/internal/player.hh"

_INITIALIZE_EASYLOGGINGPP


namespace buildingblocks {
namespace engine {


Engine::Engine(int argc, const char **argv)
{
    _START_EASYLOGGINGPP(argc, argv);

    LDEBUG << "Engine initialized";
}

Engine::~Engine(void)
{
}

void Engine::setBoard(internal::Board *board_)
{
    this->board_ = board_;
}

internal::Board *Engine::board(void) const
{
    return board_;
}


} // namespace engine
} // namespace buildingblocks

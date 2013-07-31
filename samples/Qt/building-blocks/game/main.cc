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

#include "gameplay.hh"
#include "engine/engine.hh"
#include "engine/easylogging++.h"

#include <QApplication>

int main(int argc, char** argv)
{
    QApplication a(argc, argv);
    buildingblocks::engine::Engine* gameEngine = new buildingblocks::engine::Engine(argc, const_cast<const char**>(argv));
    buildingblocks::GamePlay* w = new buildingblocks::GamePlay(gameEngine);
    w->show();
    int status = a.exec();
    delete w;
    return status;
}

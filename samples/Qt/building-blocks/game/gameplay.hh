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

#ifndef BUILDING_BLOCKS_GAMEPLAY_HH
#define BUILDING_BLOCKS_GAMEPLAY_HH

#include "game/gameboard.hh"

#include <QMainWindow>
#include <QtGui/QMainWindow>

#define DELETE(var) if (var != NULL) { delete var; var = NULL; }

class QLabel;
class QPushButton;

namespace buildingblocks {

namespace engine {

class Engine;

namespace internal {

class Player;

} // namespace internal
} // namespace engine


class GamePlay : public QMainWindow
{
    Q_OBJECT
    
public:

    explicit GamePlay(engine::Engine *gameEngine_);
    explicit GamePlay(buildingblocks::engine::Engine* gameEngine_, buildingblocks::GameBoard* gameBoard_);

    virtual ~GamePlay();

    buildingblocks::engine::Engine* gameEngine(void) const;
    buildingblocks::GameBoard* gameBoard(void) const;

    void paintEvent(QPaintEvent *);
protected:
    QWidget* centralWidget;
    QLabel* playerTurnLabel;
    QLabel* player1Legend;
    QLabel* player2Legend;
    QLabel* selectionLegend;
    QPushButton* resetButton;
private:
    void init(buildingblocks::engine::Engine* gameEngine_, buildingblocks::GameBoard* gameBoard_);
    buildingblocks::engine::Engine* gameEngine_;
    buildingblocks::GameBoard* gameBoard_;
    void setupUi();
    void retranslateUi();
public slots:
    void boardUpdated(buildingblocks::engine::internal::Player* player);
    void reset(void);
};

} //namespace buildingblocks
#endif // BUILDING_BLOCKS_GAMEPLAY_HH

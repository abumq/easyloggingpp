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

#ifndef GAMEBOARD_HH
#define GAMEBOARD_HH

#include "engine/internal/board.hh"

#include <QWidget>
#include <QGraphicsView>

class QPainter;
class QGraphicsScene;
class QLabel;

namespace buildingblocks {

namespace engine {
namespace internal {

class Point;

} // namespace internal
} // namespace engine

class GameBoard : public QGraphicsView, public buildingblocks::engine::internal::Board
{
    Q_OBJECT
public:
    explicit GameBoard(QWidget *parent_ = 0, unsigned int totalPointsOnX_ = 20, unsigned int totalPointsOnY_ = 20, unsigned int boardWidth_ = 100, unsigned int boardHeight_ = 100, unsigned int startCoord_ = 0, const std::string& name_ = "Default Board", kPlayerTurn playerTurn_ = kPlayer1);
    virtual ~GameBoard(void);
    void mousePressEvent(QMouseEvent *event);
    void setGeometry(const QRect &rect);
    void setGeometry(int x, int y, int w, int h);
    QColor getPlayerQColor(buildingblocks::engine::internal::Player* player = 0) const;
    buildingblocks::engine::internal::Player* currentPlayer(void) const;
    virtual void reset(void);
signals:
    void updated(buildingblocks::engine::internal::Player* player);
public slots:
    
private:
    // First point used to make line
    buildingblocks::engine::internal::Point* lastPoint;
    QGraphicsEllipseItem* lastVisiblePoint;
    buildingblocks::engine::internal::Player* currentPlayer_;
    void initializeVisiblePoints(void);
    void drawPoint(buildingblocks::engine::internal::Point* point);
    void drawLine(QGraphicsEllipseItem* ellipse, buildingblocks::engine::internal::Line* line);
    QGraphicsScene* scene_;
};
}
#endif // GAMEBOARD_HH

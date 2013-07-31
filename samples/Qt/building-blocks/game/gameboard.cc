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

#include "gameboard.hh"
#include "engine/easylogging++.h"
#include "engine/internal/point.hh"
#include "engine/internal/line.hh"
#include "engine/internal/player.hh"

#include <QBrush>
#include <QMouseEvent>
#include <QGraphicsScene>
#include <QGraphicsEllipseItem>
#include <QGraphicsLineItem>
#include <QLabel>

namespace buildingblocks {

GameBoard::GameBoard(QWidget *parent_, unsigned int totalPointsOnX_, unsigned int totalPointsOnY_,
                     unsigned int boardWidth_, unsigned int boardHeight_, unsigned int startCoord_,
                     const std::string &name_, kPlayerTurn playerTurn_) :
    QGraphicsView(parent_),
    buildingblocks::engine::internal::Board(totalPointsOnX_, totalPointsOnY_, boardWidth_, boardHeight_, startCoord_, name_, playerTurn_),
    lastPoint(NULL),
    lastVisiblePoint(NULL)
{
    scene_ = new QGraphicsScene(0, 0, boardWidth(), boardHeight());

    setScene(scene_);
    setAttribute(Qt::WA_PaintOutsidePaintEvent);
    initializeVisiblePoints();
    currentPlayer_ = playerWithTurn();
}

GameBoard::~GameBoard(void)
{
    delete scene_;
}

void GameBoard::initializeVisiblePoints()
{
    scene_->clear();
    viewport()->update();
    QPen blackPen(Qt::black);
    blackPen.setWidth(1);
    for (unsigned int i = 0; i < Board::totalPoints(); ++i) {
        buildingblocks::engine::internal::Point* point = points().at(i);
        QGraphicsEllipseItem *visiblePoint = scene_->addEllipse(point->x(), point->y(), point->diameter(), point->diameter(), blackPen);
    }
}

void GameBoard::mousePressEvent(QMouseEvent *event)
{
    if (event->button() == Qt::LeftButton) {
        buildingblocks::engine::internal::Point* point = findNearestPointByApproxCoords(event->x(), event->y());
        if (point == NULL) {
            LVERBOSE(4) << "No point found near [" << event->x() << ", " << event->y() << "]";
            return;
        }
        LVERBOSE(4) << "Found point " << point << " near [" << event->x() << ", " << event->y() << "]";
        drawPoint(point);

    } else if (event->button() == Qt::RightButton) {
        if (lastPoint != NULL) {
            LVERBOSE(4) << "Dereferencing point " << lastPoint;
            lastPoint = NULL;
            delete lastVisiblePoint;
            lastVisiblePoint = NULL;
        }
    }
}

void GameBoard::drawPoint(buildingblocks::engine::internal::Point *point)
{
    QPen playerPen(getPlayerQColor());
    playerPen.setWidth(1);
    QBrush playerBrush(getPlayerQColor());
    QBrush selectedBrush(Qt::yellow);

    QGraphicsEllipseItem* newVisiblePoint = scene_->addEllipse(point->x(), point->y(), point->diameter(), point->diameter(), playerPen, playerBrush);

    if (lastPoint == NULL && lastVisiblePoint == NULL) {
        lastPoint = point;
        lastVisiblePoint = newVisiblePoint;
        lastVisiblePoint->setBrush(selectedBrush);
    } else {
        buildingblocks::engine::internal::Line* line = new buildingblocks::engine::internal::Line(lastPoint, point);
        lastVisiblePoint->setBrush(playerBrush);
        drawLine(newVisiblePoint, line);
        lastVisiblePoint = NULL;
        lastPoint = NULL;
    }
}

void GameBoard::drawLine(QGraphicsEllipseItem* currentVisiblePoint, buildingblocks::engine::internal::Line* line)
{
    QPen playerPen(getPlayerQColor());
    playerPen.setWidth(1);

    int turnResult = addLine(line, currentPlayer_);
    currentPlayer_ = playerWithTurn();
    emit updated(currentPlayer_);
    if (turnResult == kMadeLine) {
        scene_->addLine(line->start()->x() + (line->start()->diameter() / 2),
                        line->start()->y() + (line->start()->diameter() / 2),
                        line->end()->x()  + (line->start()->diameter() / 2),
                        line->end()->y() + (line->end()->diameter() / 2),
                        playerPen);
    } else if (turnResult == kMadeBlock) {
        // Make block
        // Assign player color to it
    } else {
        // Invalid turn
        delete currentVisiblePoint;
        delete lastVisiblePoint;
        delete line;
    }
}

QColor GameBoard::getPlayerQColor(engine::internal::Player *player) const
{
    // FIXME: good idea to return like this? scope issue?
    if (player == NULL) {
        return QColor(currentPlayer_->color().r(), currentPlayer_->color().g(), currentPlayer_->color().b());
    }
    return QColor(player->color().r(), player->color().g(), player->color().b());
}

engine::internal::Player *GameBoard::currentPlayer() const
{
    return currentPlayer_;
}

void GameBoard::reset(void)
{
    Board::reset();
    lastPoint = NULL;
    delete lastVisiblePoint;
    lastVisiblePoint = NULL;
    initializeVisiblePoints();
    currentPlayer_ = playerWithTurn();
    emit updated(currentPlayer_);
}

void GameBoard::setGeometry(const QRect& rect)
{
    QWidget::setGeometry(rect);
    Board::resize(rect.width(), rect.height());
}

void GameBoard::setGeometry(int x, int y, int w, int h)
{
    QWidget::setGeometry(x, y, w, h);
    Board::resize(w, h);
}


} // namespace buildingblocks

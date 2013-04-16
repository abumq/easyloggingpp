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

#include "engine/internal/board.hh"
#include "engine/easylogging++.h"
#include "engine/internal/point.hh"
#include "engine/internal/player.hh"
#include "engine/internal/line.hh"
#include "engine/internal/block.hh"

#include <complex>
#include <vector>
#include <iterator>
#include <algorithm>

namespace buildingblocks {

namespace engine {

namespace internal {

Board::Board(const Board &board)
{
    clearBlocks();
    clearLines();
    clearPoints();
    init(board.totalPointsOnX_, board.totalPointsOnY_, board.boardWidth_, board.boardHeight_, board.startCoord_, board.name_, board.playerTurn_);
}

Board::Board(unsigned int totalPointsOnX_, unsigned int totalPointsOnY_, unsigned int boardWidth_, unsigned int boardHeight_, unsigned int startCoord_, const std::string &name_, kPlayerTurn playerTurn_)
{
    init(totalPointsOnX_, totalPointsOnY_, boardWidth_, boardHeight_, startCoord_, name_, playerTurn_);
}

Board& Board::operator=(const Board& board)
{
    clearBlocks();
    clearLines();
    clearPoints();
    init(board.totalPointsOnX_, board.totalPointsOnY_, board.boardWidth_, board.boardHeight_, board.startCoord_, board.name_, board.playerTurn_);
    return *this;
}

void Board::init(unsigned int totalPointsOnX_, unsigned int totalPointsOnY_, unsigned int boardWidth_, unsigned int boardHeight_, unsigned int startCoord_, const std::string &name_, kPlayerTurn playerTurn_)
{
    if (totalPointsOnX_ < 5 || totalPointsOnX_ > 200 || totalPointsOnY_ < 5 || totalPointsOnY_ > 200 || boardWidth_ < 10 || boardHeight_ < 10) {
        BERROR << "Invalid dimensions [" << totalPointsOnX_ << " x " << totalPointsOnY_ << "]";
        return;
    }

    BWARNING_IF ((boardHeight_ * boardWidth_) < (totalPointsOnX_ * totalPointsOnY_)) <<
             "Board dimension is too small for [" << (totalPointsOnX_ * totalPointsOnY_) << "] points";

    this->totalPointsOnX_ = totalPointsOnX_;
    this->totalPointsOnY_ = totalPointsOnY_;
    this->pointsDistanceX_ = (boardWidth_ / totalPointsOnX_);
    this->pointsDistanceY_ = (boardHeight_ / totalPointsOnY_);
    this->boardWidth_ = boardWidth_;
    this->boardHeight_ = boardHeight_;
    this->name_ = name_;
    this->playerTurn_ = playerTurn_;
    this->startCoord_ = startCoord_;
    plot();
    initializePlayers(playerTurn_);
}

Board::~Board(void)
{
    clearBlocks();
    clearLines();
    clearPoints();
    clearPlayers();
}

std::string Board::name(void) const
{
    return name_;
}

unsigned int Board::totalPointsOnX(void) const
{
    return totalPointsOnX_;
}

unsigned int Board::totalPointsOnY(void) const
{
    return totalPointsOnY_;
}

unsigned int Board::pointsDistanceX(void) const
{
    return pointsDistanceX_;
}

unsigned int Board::pointsDistanceY(void) const
{
    return pointsDistanceY_;
}

unsigned int Board::boardWidth(void) const
{
    return boardWidth_;
}

unsigned int Board::boardHeight(void) const
{
    return boardHeight_;
}

unsigned int Board::totalPoints(void) const
{
    return points_.size();
}

unsigned int Board::totalLines(void) const
{
    return lines_.size();
}

unsigned int Board::totalBlocks(void) const
{
    return blocks_.size();
}

std::vector<buildingblocks::engine::internal::Point *> Board::points(void) const
{
    return points_;
}

std::vector<buildingblocks::engine::internal::Player *> Board::players(void) const
{
    return players_;
}

std::vector<buildingblocks::engine::internal::Line *> Board::lines(void) const
{
    return lines_;
}

std::vector<buildingblocks::engine::internal::Block*> Board::blocks(void) const
{
    return blocks_;
}

void Board::setBoardWidth(unsigned int boardWidth_)
{
    this->boardWidth_ = boardWidth_;
    oldDistanceX_ = pointsDistanceX();
    this->pointsDistanceX_ = (boardWidth_ / (totalPointsOnX()));
    adjustPoints();
}

void Board::setBoardHeight(unsigned int boardHeight_)
{
    this->boardHeight_ = boardHeight_;
    oldDistanceY_ = pointsDistanceY();
    this->pointsDistanceY_ = (boardHeight_ / (totalPointsOnY()));
    adjustPoints();
}

std::ostream& operator<<(std::ostream& ss, const Board& board_)
{
    ss << board_.name();
    return ss;
}

void Board::reset(void)
{
    LVERBOSE(1) << "Resetting board";
    clearBlocks();
    clearLines();
    clearPlayers();
    initializePlayers(playerTurn_);
}

void Board::resize(unsigned int boardWidth_, unsigned int boardHeight_)
{
    this->boardWidth_ = boardWidth_;
    oldDistanceX_ = pointsDistanceX();
    pointsDistanceX_ = (boardWidth_ / (totalPointsOnX()));
    this->boardHeight_ = boardHeight_;
    oldDistanceY_ = pointsDistanceY();
    pointsDistanceY_ = (boardHeight_ / (totalPointsOnY()));
    adjustPoints();
}

buildingblocks::engine::internal::Line* Board::findLine(const buildingblocks::engine::internal::Line& exactLine_)
{
    buildingblocks::engine::internal::LinePredicate linePredicate(exactLine_);
    buildingblocks::engine::internal::LineIterator lineIter = std::find_if(lines_.begin(), lines_.end(), linePredicate);
    if (lineIter != lines_.end() && *lineIter != NULL) {
        return *lineIter;
    }
    return NULL;
}

std::vector<buildingblocks::engine::internal::Line*> Board::findParallelLines(const buildingblocks::engine::internal::Line* exactLine_)
{
    std::vector<buildingblocks::engine::internal::Line*> parallelLines;
    if (exactLine_ == NULL) {
        BERROR << "Line to find parallel lines for cannot be NULL";
        return parallelLines;
    }
    Line* foundLine = NULL;
    buildingblocks::engine::internal::Point *point1Start = NULL;
    buildingblocks::engine::internal::Point *point1End = NULL;
    buildingblocks::engine::internal::Line *side1Line = NULL;
    buildingblocks::engine::internal::Point *point2Start = NULL;
    buildingblocks::engine::internal::Point *point2End = NULL;
    buildingblocks::engine::internal::Line *side2Line = NULL;
    if (exactLine_->isVertical()) {
        // Right
        point1Start = new buildingblocks::engine::internal::Point(1, exactLine_->start()->x() + pointsDistanceX(), exactLine_->start()->y());
        point1End = new buildingblocks::engine::internal::Point(1, exactLine_->end()->x() + pointsDistanceX(), exactLine_->end()->y());
        side1Line = new buildingblocks::engine::internal::Line(point1Start, point1End);

        // Left
        point2Start = new buildingblocks::engine::internal::Point(1, exactLine_->start()->x() - pointsDistanceX(), exactLine_->start()->y());
        point2End = new buildingblocks::engine::internal::Point(1, exactLine_->end()->x() - pointsDistanceX(), exactLine_->end()->y());
        side2Line = new buildingblocks::engine::internal::Line(point1Start, point1End);
    } else {
        // Horizontal
        // Above
        point1Start = new buildingblocks::engine::internal::Point(0, exactLine_->start()->x(), exactLine_->start()->y() - pointsDistanceY());
        point1End = new buildingblocks::engine::internal::Point(0, exactLine_->end()->x(), exactLine_->end()->y() - pointsDistanceY());
        side1Line = new buildingblocks::engine::internal::Line(point1Start, point1End);

        // Below
        point2Start = new buildingblocks::engine::internal::Point(1, exactLine_->start()->x(), exactLine_->start()->y() + pointsDistanceY());
        point2End = new buildingblocks::engine::internal::Point(1, exactLine_->end()->x(), exactLine_->end()->y() + pointsDistanceY());
        side2Line = new buildingblocks::engine::internal::Line(point2Start, point2End);
    }
    foundLine = findLine(*side1Line);
    if (foundLine != NULL) {
        parallelLines.push_back(foundLine);
    }
    if (*side1Line == *side2Line) {
        LWARNING << "Skipping check for duplicate predicate line";
    } else {
        foundLine = findLine(*side2Line);
        if (foundLine != NULL) {
            parallelLines.push_back(foundLine);
        }
    }

    delete point1Start;
    delete point1End;
    delete side1Line;
    delete point2Start;
    delete point2End;
    delete side2Line;
    unsigned int totalParallelLines = parallelLines.size();
    BVERBOSE(5) << "[" << totalParallelLines << "] line" << (totalParallelLines > 1 ? "s" : "") << " found parallel to " << exactLine_;
    return parallelLines;
}

std::vector<buildingblocks::engine::internal::Line *> Board::findPerpendicularLines(const buildingblocks::engine::internal::Line *exactLine_)
{
    std::vector<buildingblocks::engine::internal::Line*> perpendicularLines;
    if (exactLine_ == NULL) {
        BERROR << "Line to find perpendicular lines for cannot be NULL";
        return perpendicularLines;
    }
    if (exactLine_->isVertical()) {
        buildingblocks::engine::internal::Line* rightAngledStart = findRotatedLine(exactLine_, kStart, kRight);
        if (rightAngledStart != NULL) {
            perpendicularLines.push_back(rightAngledStart);
        }
        buildingblocks::engine::internal::Line* leftAngledStart = findRotatedLine(exactLine_, kStart, kLeft);
        if (leftAngledStart != NULL) {
            perpendicularLines.push_back(leftAngledStart);
        }
        buildingblocks::engine::internal::Line* rightAngledEnd = findRotatedLine(exactLine_, kEnd, kRight);
        if (rightAngledEnd != NULL) {
            perpendicularLines.push_back(rightAngledEnd);
        }
        buildingblocks::engine::internal::Line* leftAngledEnd = findRotatedLine(exactLine_, kEnd, kLeft);
        if (leftAngledEnd != NULL) {
            perpendicularLines.push_back(leftAngledEnd);
        }
    } else {
        buildingblocks::engine::internal::Line* leftAngledStart = findRotatedLine(exactLine_, kStart, kLeft);
        if (leftAngledStart != NULL) {
            perpendicularLines.push_back(leftAngledStart);
        }
        buildingblocks::engine::internal::Line* rightAngledStart = findRotatedLine(exactLine_, kStart, kRight);
        if (rightAngledStart != NULL) {
            perpendicularLines.push_back(rightAngledStart);
        }
        buildingblocks::engine::internal::Line* leftAngledEnd = findRotatedLine(exactLine_, kEnd, kLeft);
        if (leftAngledEnd != NULL) {
            perpendicularLines.push_back(leftAngledEnd);
        }
        buildingblocks::engine::internal::Line* rightAngledEnd = findRotatedLine(exactLine_, kEnd, kRight);
        if (rightAngledEnd != NULL) {
            perpendicularLines.push_back(rightAngledEnd);
        }
    }
}

buildingblocks::engine::internal::Line *Board::findRotatedLine(const buildingblocks::engine::internal::Line* originalLine_, Board::kRotationPoint rotationPoint_, Board::kRotationDirection direction_)
{
    // FIXME: This is incomplete
    // The values below are test values only, you may use originalLine_'s values
    const float angle = -90.0;
    const float degreePerRadian = 57.2957795;
    const float s = sin(angle / degreePerRadian);
    const float c = cos(angle / degreePerRadian);
    int p1x = 320;
    int p1y = 480;
    int p2x = 320;
    int p2y = 320;

    float centerX = (p2x - p1x) / 2 + p1x;
    float centerY = (p2y - p1y) / 2 + p1y;
    p2x -= centerX;
    p2y -= centerY;
    double newX = centerX + (p2x * c - p2y * s);
    double newY = centerY + (p2x * s + p2y * c);

    LDEBUG << "New point: (" << newX << ", " << newY << ")";

}

buildingblocks::engine::internal::Point* Board::findPoint(const buildingblocks::engine::internal::Point& approxPoint)
{
    buildingblocks::engine::internal::PointPredicate pointPredicate(approxPoint);
    buildingblocks::engine::internal::PointIterator pointIter = std::find_if(points_.begin(), points_.end(), pointPredicate);
    if (pointIter != points().end() && *pointIter != NULL) {
        return *pointIter;
    }
    return NULL;
}

buildingblocks::engine::internal::Point *Board::findNearestPointByApproxCoords(unsigned int x_, unsigned int y_, unsigned int diameter_)
{
    return findPoint(buildingblocks::engine::internal::Point(0, x_, y_, diameter_));
}

std::vector<buildingblocks::engine::internal::Point *> Board::findNearestPoints(const buildingblocks::engine::internal::Point* exactPoint)
{
    std::vector<buildingblocks::engine::internal::Point *> nearestPoints;
    buildingblocks::engine::internal::Point* point = NULL;

    unsigned int x  = exactPoint->x();
    unsigned int y = exactPoint->y();
    unsigned int dx = pointsDistanceX();
    unsigned int dy = pointsDistanceY();

    if (x == startCoord_ && y == startCoord_) {
        // top-left edge
        // x+
        point = findNearestPointByApproxCoords(x + dx, y);
        nearestPoints.push_back(point);
        // y+
        point = findNearestPointByApproxCoords(x, y + dy);
        nearestPoints.push_back(point);
    } else if ((x == (dx * totalPointsOnX()) - dx) && y == startCoord_) {
        // top-right edge
        // x-
        point = findNearestPointByApproxCoords(x - dx, y);
        nearestPoints.push_back(point);
        // y+
        point = findNearestPointByApproxCoords(x, y + dy);
        nearestPoints.push_back(point);
    } else if ((x == (dx * totalPointsOnX()) - dx) && (y == (dy * totalPointsOnY()) - dy)) {
        // bottom-right edge
        // x-
        point = findNearestPointByApproxCoords(x - dx, y);
        nearestPoints.push_back(point);
        // y-
        point = findNearestPointByApproxCoords(x, y - dy);
        nearestPoints.push_back(point);
    } else if (x == startCoord_ && (y == (dy * totalPointsOnY()) - dy)) {
        // bottom-left edge
        // x+
        point = findNearestPointByApproxCoords(x + dx, y);
        nearestPoints.push_back(point);
        // y-
        point = findNearestPointByApproxCoords(x, y - dy);
        nearestPoints.push_back(point);
    } else if (x == startCoord_ && y != startCoord_ && y % dy == startCoord_) {
        // middle of first column
        // x+
        point = findNearestPointByApproxCoords(x + dx, y);
        nearestPoints.push_back(point);
        // y+
        point = findNearestPointByApproxCoords(x, y + dy);
        nearestPoints.push_back(point);
        // y-
        point = findNearestPointByApproxCoords(x, y - dy);
        nearestPoints.push_back(point);
    } else if (x == (dx * totalPointsOnX()) - dx && y != startCoord_ && y % dy == startCoord_) {
        // middle of last column
        // y+
        point = findNearestPointByApproxCoords(x, y + dy);
        nearestPoints.push_back(point);
        // x-
        point = findNearestPointByApproxCoords(x - dx, y);
        nearestPoints.push_back(point);
        // y-
        point = findNearestPointByApproxCoords(x, y - dy);
        nearestPoints.push_back(point);
    } else if (x % dx == startCoord_ && y == startCoord_) {
        // middle of first row
        // x+
        point = findNearestPointByApproxCoords(x + dx, y);
        nearestPoints.push_back(point);
        // y+
        point = findNearestPointByApproxCoords(x, y + dy);
        nearestPoints.push_back(point);
        // x-
        point = findNearestPointByApproxCoords(x - dx, y);
        nearestPoints.push_back(point);
    } else if (x != startCoord_ && x % dx == startCoord_ && y == (dy * totalPointsOnY()) - dy) {
        // middle of last row
        // x+
        point = findNearestPointByApproxCoords(x + dx, y);
        nearestPoints.push_back(point);
        // x-
        point = findNearestPointByApproxCoords(x - dx, y);
        nearestPoints.push_back(point);
        // y-
        point = findNearestPointByApproxCoords(x, y - dy);
        nearestPoints.push_back(point);
    } else {
        // middle of the board
        // x+
        point = findNearestPointByApproxCoords(x + dx, y);
        nearestPoints.push_back(point);
        // y+
        point = findNearestPointByApproxCoords(x, y + dy);
        nearestPoints.push_back(point);
        // x-
        point = findNearestPointByApproxCoords(x - dx, y);
        nearestPoints.push_back(point);
        // y-
        point = findNearestPointByApproxCoords(x, y - dy);
        nearestPoints.push_back(point);
    }
    unsigned int totalNearestPoints = nearestPoints.size();
    BVERBOSE(5) << "[" << totalNearestPoints << "] point" << (totalNearestPoints > 1 ? "s" : "") << " found near [" << exactPoint << "]";
    return nearestPoints;
}

bool Board::determineIfLineMakesBlock(const buildingblocks::engine::internal::Line* const line_, buildingblocks::engine::internal::Block* targetBlock) {

    std::vector<buildingblocks::engine::internal::Line*> parallelLines = findParallelLines(line_);
    for (unsigned int i = 0; i < parallelLines.size(); ++i) {
        std::vector<buildingblocks::engine::internal::Line*> perpendicularLines = findPerpendicularLines(parallelLines.at(i));
        for (unsigned int j = 0; j < perpendicularLines.size(); ++j) {
            // HERE ONWARDS, ITS INCOMPLETE
        }
    }
    return false;
}

void Board::adjustPoints(void)
{
    //FIXME: board doesnt re-adjust points yet
    unsigned int differenceX = pointsDistanceX() - oldDistanceX_;
    unsigned int differenceY = pointsDistanceY() - oldDistanceY_;
    for (unsigned int i = 0; i < totalPoints(); ++i) {
        buildingblocks::engine::internal::Point* point = points_.at(i);
        point->reset(point->x() + differenceX, point->y() + differenceY);
    }
}

void Board::plot(void)
{
    LVERBOSE(1) << "Constructing board [" << this << "] of dimensions [" << totalPointsOnX() << ", " << totalPointsOnY() << "] and distance [" << pointsDistanceX() << ", " << pointsDistanceY() << "] in each point";
    unsigned int currentX = startCoord_;
    unsigned int currentY = startCoord_;
    unsigned int id = 0;
    for (unsigned int h = totalPointsOnY(); h >= 1 ; --h) {
        for (unsigned int w = totalPointsOnX(); w >= 1 ; --w) {
            createPoint(++id, currentX, currentY);
            currentX += pointsDistanceX();
        }
        currentX = startCoord_;
        currentY += pointsDistanceY();
    }
    LVERBOSE(1) << "Constructed board with [" << points_.size() << "] points and distance [" << pointsDistanceX() << ", " << pointsDistanceY() << "]";
}

void Board::createPoint(unsigned int id, unsigned int x, unsigned int y)
{
    buildingblocks::engine::internal::Point* currentPoint = new buildingblocks::engine::internal::Point(id, x, y);
    LVERBOSE(4) << "Creating point on board " << *currentPoint;
    points_.push_back(currentPoint);
}

void Board::clearPoints(void)
{
    for (unsigned int i = 0; i < totalPoints(); ++i) {
        delete points_.at(i);
    }
    points_.clear();
}

void Board::clearPlayers(void)
{
    for (unsigned int i = 0; i < players_.size(); ++i) {
        delete players_.at(i);
    }
    players_.clear();
}

void Board::clearBlocks(void)
{
    for (unsigned int i = 0; i < blocks_.size(); ++i) {
        delete blocks_.at(i);
    }
    blocks_.clear();
}

void Board::clearLines(void)
{
    for (unsigned int i = 0; i < lines_.size(); ++i) {
        delete lines_.at(i);
    }
    lines_.clear();
}

buildingblocks::engine::internal::Player* Board::playerWithTurn(void)
{
    buildingblocks::engine::internal::PlayerPredicateByTurn predicate(true);
    buildingblocks::engine::internal::PlayerIterator playerIter = std::find_if(players_.begin(), players_.end(), predicate);
    if (playerIter != players_.end() && *playerIter != NULL) {
        return *playerIter;
    } else {
        // This should not be possible
        return NULL;
    }
}

void Board::nextPlayer(void)
{
    playerWithTurn()->setHasTurn(false);
    LVERBOSE(2) << "[" << *playerWithTurn() << "] has turn";
}

void Board::initializePlayers(kPlayerTurn playerTurn)
{
    buildingblocks::engine::internal::Player* player1 = new buildingblocks::engine::internal::Player("Player 1", buildingblocks::engine::internal::Color::pickRandom(10));
    buildingblocks::engine::internal::Player* player2 = new buildingblocks::engine::internal::Player("Player 2", buildingblocks::engine::internal::Color::pickRandom(100));
    player2->setOpponent(player1);
    addPlayer(player1);
    addPlayer(player2);

    if (playerTurn == kPlayer1) {
        player1->setHasTurn(true);
    } else {
        player2->setHasTurn(true);
    }
}

int Board::addLine(buildingblocks::engine::internal::Line *line, buildingblocks::engine::internal::Player* player)
{
    if (!isLegalToAddLine(line)) {
        BERROR << "Adding line " << *line << " is not valid as per game rules!";
        return kInvalidTurn;
    }

    LVERBOSE(2) << "[" << *player << "] has put line " << line;
    lines_.push_back(line);
    buildingblocks::engine::internal::Block* block = NULL;
    if (determineIfLineMakesBlock(line, block)) {
        block->setOwner(player);
        blocks_.push_back(block);
        return kMadeBlock;
    } else {
        nextPlayer();
        return kMadeLine;
    }
}

bool Board::isLegalToAddLine(const buildingblocks::engine::internal::Line *line)
{
    LVERBOSE(3) << "Checking if line [" << *line << "] is legal as per game rules";
    unsigned int distance_ = line->start()->distance(*line->end());

    LVERBOSE(3) << "Distance for points " << distance_;
    bool distanceOk = distance_ == pointsDistanceX() || distance_ == pointsDistanceY();

    // FIXME: Make sure line doesnt get duplicated to prevent line over another line

    bool lineAlreadyExist = false;

    BERROR_IF(lineAlreadyExist) << "Line [" << *line << "] already exist";
    return distanceOk && !lineAlreadyExist;
}

void Board::addPlayer(buildingblocks::engine::internal::Player* player_)
{
    if (player_ == NULL) {
        BERROR << "New player cannot be NULL";
        return;
    }
    if (players_.size() == 2) {
        BWARNING << "Already have two players, replacing player [" << *players_.at(0) << "] with [" << *player_ << "]";
        delete players_[0];
        players_[0] = player_;
    } else {
        LVERBOSE(2) << "Adding player [" << *player_ << "]";
        players_.push_back(player_);
    }
}
} // namespace internal
} // namespace engine
} // namespace buildingblocks

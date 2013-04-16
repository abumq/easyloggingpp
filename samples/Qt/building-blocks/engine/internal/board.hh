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

#ifndef BUILDING_BLOCKS_ENGINE_BOARD_HH
#define BUILDING_BLOCKS_ENGINE_BOARD_HH

#include <vector>
#include <string>

namespace buildingblocks {

namespace engine {

namespace internal {

class Point;
typedef std::vector<Point*>::iterator PointIterator;

class Player;
typedef std::vector<Player*>::iterator PlayerIterator;

class Line;
typedef std::vector<Line*>::iterator LineIterator;

class Block;
typedef std::vector<Block*>::iterator BlockIterator;

class Board
{
public:
    enum kPlayerTurn { kPlayer1, kPlayer2 };
    enum kTurnResult { kMadeBlock, kMadeLine, kInvalidTurn };
    enum kRotationPoint { kStart, kEnd };
    enum kRotationDirection { kRight, kLeft };
    explicit Board(const Board& board);
    explicit Board(unsigned int totalPointsOnX_, unsigned int totalPointsOnY_, unsigned int boardWidth_, unsigned int boardHeight_, unsigned int startCoord_ = 0, const std::string& name_ = "Default Board", kPlayerTurn playerTurn = kPlayer1);
    Board& operator=(const Board& board);
    virtual ~Board(void);
    std::string name(void) const;
    unsigned int totalPointsOnX(void) const;
    unsigned int totalPointsOnY(void) const;
    unsigned int pointsDistanceX(void) const;
    unsigned int pointsDistanceY(void) const;
    unsigned int boardWidth(void) const;
    unsigned int boardHeight(void) const;
    void setBoardWidth(unsigned int boardWidth_);
    void setBoardHeight(unsigned int boardHeight_);
    friend std::ostream& operator<<(std::ostream& ss, const Board& board_);
    virtual void reset(void);
    std::vector<buildingblocks::engine::internal::Player*> players(void) const;
protected:

    buildingblocks::engine::internal::Line* findLine(const buildingblocks::engine::internal::Line& exactLine_);
    buildingblocks::engine::internal::Line* findRotatedLine(const buildingblocks::engine::internal::Line* originalLine_, kRotationPoint rotationPoint_, kRotationDirection direction_);
    /**
     * Find lines parallel to provided line. This can be total lines in range 0-2, for vertical line there will be one on left
     * and other on right while for horizontal line, one above other below the line
     * @param exactLine
     * @return List of pointers to lines parallel to exactLine
     */
    std::vector<buildingblocks::engine::internal::Line *> findParallelLines(const buildingblocks::engine::internal::Line* exactLine_);
    std::vector<buildingblocks::engine::internal::Line *> findPerpendicularLines(const buildingblocks::engine::internal::Line* exactLine_);
    /**
     * Finds exact point approximate to provided point.
     * @param approxPoint
     * @return Pointer to point
     */
    buildingblocks::engine::internal::Point* findPoint(const buildingblocks::engine::internal::Point& approxPoint);

    /**
     * Finds nearest point to provided coordinates and diameter.
     * @param x_ x-axis
     * @param y_ y-axis
     * @param diameter_ Diameter used when approximating
     * @return Pointer to point
     */
    buildingblocks::engine::internal::Point* findNearestPointByApproxCoords(unsigned int x_, unsigned int y_, unsigned int diameter_ = 10);

    /**
     * Finds all points near to provided point.
     * @param exactPoint Exact point to find nearest points for. Remember, this cannot be an approximate point.
     * @return List of pointers to nearest points ordered in clock wise (x+, y+, x-, y-)
     */
    std::vector<buildingblocks::engine::internal::Point*> findNearestPoints(const buildingblocks::engine::internal::Point* exactPoint);
    inline buildingblocks::engine::internal::Player* playerWithTurn(void);
    inline void nextPlayer(void);
    inline void initializePlayers(kPlayerTurn playerTurn = kPlayer1);
    int addLine(buildingblocks::engine::internal::Line* line, buildingblocks::engine::internal::Player* player);
    bool isLegalToAddLine(const buildingblocks::engine::internal::Line* line);
    void resize(unsigned int boardWidth_, unsigned int boardHeight_);
    std::vector<buildingblocks::engine::internal::Line*> lines(void) const;
    std::vector<buildingblocks::engine::internal::Block*> blocks(void) const;
    std::vector<buildingblocks::engine::internal::Point*> points(void) const;

    unsigned int totalPoints(void) const;
    unsigned int totalLines(void) const;
    unsigned int totalBlocks(void) const;
private:
    std::string name_;
    unsigned int totalPointsOnX_;
    unsigned int totalPointsOnY_;
    unsigned int pointsDistanceX_;
    unsigned int pointsDistanceY_;
    unsigned int boardWidth_;
    unsigned int boardHeight_;
    unsigned int oldDistanceX_;
    unsigned int oldDistanceY_;
    unsigned int startCoord_;
    kPlayerTurn playerTurn_;

    void clearPoints(void);
    void clearPlayers(void);
    void clearBlocks(void);
    void clearLines(void);
    void plot(void);
    void createPoint(unsigned int id, unsigned int x, unsigned int y);
    void init(unsigned int totalPointsOnX_, unsigned int totalPointsOnY_, unsigned int boardWidth_, unsigned int boardHeight_, unsigned int startCoord_, const std::string &name_, kPlayerTurn playerTurn);
    void adjustPoints(void);
    bool determineIfLineMakesBlock(const buildingblocks::engine::internal::Line* const line_, buildingblocks::engine::internal::Block* targetBlock);
    void addPlayer(buildingblocks::engine::internal::Player* player_);
    std::vector<buildingblocks::engine::internal::Point*> points_;
    std::vector<buildingblocks::engine::internal::Player*> players_;
    std::vector<buildingblocks::engine::internal::Line*> lines_;
    std::vector<buildingblocks::engine::internal::Block*> blocks_;
};


} // namespace internal
} // namespace engine
} // namespace buildingblocks
#endif // BUILDING_BLOCKS_ENGINE_BOARD_HH


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

#ifndef BUILDING_BLOCKS_ENGINE_PLAYER_HH
#define BUILDING_BLOCKS_ENGINE_PLAYER_HH

#include <cstdlib>
#include <ctime>

#include <string>

namespace buildingblocks {

namespace engine {

namespace internal {

class Color {
public:
    explicit Color(unsigned int r_, unsigned int g_, unsigned int b_) :
        r_(r_),
        g_(g_),
        b_(b_)
    {}
    inline bool operator==(const Color& color) {
        return r() == color.r() && g() == color.g() && b() == color.b();
    }
    static Color pickRandom(int seed = 0) {
        srand(time(0) + seed);
        unsigned int r_, g_, b_;
        r_ = rand() % 150 + 50;
        b_ = rand() % 150 + 50;
        g_ = rand() % 150 + 50;
        return Color(r_, g_, b_);
    }

    inline unsigned int r(void) const {
        return r_;
    }
    inline unsigned int g(void) const {
        return g_;
    }
    inline unsigned int b(void) const {
        return b_;
    }
private:
    unsigned int r_, g_, b_;
};

class Player
{
public:
    explicit Player(const Player& player);
    explicit Player(const std::string& name_, const buildingblocks::engine::internal::Color& color_);
    virtual ~Player(void);
    Player& operator=(const Player& player);
    bool operator==(bool hasTurn_) const;
    bool operator==(const Player& player) const;
    std::string name(void) const;
    buildingblocks::engine::internal::Color color(void) const;
    bool hasTurn(void) const;
    Player* opponent(void) const;
    void setName(const std::string& name_);
    void setColor(const buildingblocks::engine::internal::Color& color_);
    void setHasTurn(bool hasTurn_);
    void setOpponent(Player* player_);
    friend std::ostream& operator<<(std::ostream& ss, const Player& player_);
private:
    std::string name_;
    buildingblocks::engine::internal::Color color_;
    bool hasTurn_;
    Player* opponent_;

};

/**
 * Assumption is that there are only two players per game
 * @brief The PlayerPredicate class
 */
class PlayerPredicateByTurn {
public:
    explicit PlayerPredicateByTurn(bool hasTurn_) :
        hasTurn_(hasTurn_) {}
    bool operator()(Player* inPlayer_) {
        return *inPlayer_ == hasTurn_;
    }
private:
    bool hasTurn_;
};
} // namespace internal
} // namespace engine
} // namespace buildingblocks

#endif // BUILDING_BLOCKS_ENGINE_PLAYER_HH

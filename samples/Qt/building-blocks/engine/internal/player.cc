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

#include "engine/internal/player.hh"
#include "engine/easylogging++.h"
namespace buildingblocks {

namespace engine {

namespace internal {

Player::Player(const Player &player) :
    name_(player.name()),
    color_(player.color()),
    hasTurn_(player.hasTurn()),
    opponent_(player.opponent())
{
}

Player::Player(const std::string& name_, const buildingblocks::engine::internal::Color& color_) :
    name_(name_),
    color_(color_),
    hasTurn_(false),
    opponent_(NULL)
{
}

Player::~Player()
{
}

Player& Player::operator=(const Player &player)
{
    this->name_ = player.name();
    this->color_ = player.color();
    this->hasTurn_ = player.hasTurn();
    this->setOpponent(player.opponent());
    return *this;
}

bool Player::operator ==(bool hasTurn_) const
{
    return (hasTurn() == hasTurn_);
}

bool Player::operator==(const Player &player) const
{
    return name() == player.name() && color() == player.color();
}

void Player::setColor(const buildingblocks::engine::internal::Color& color_)
{
    this->color_ = color_;
}

void Player::setHasTurn(bool hasTurn_)
{
    this->hasTurn_ = hasTurn_;
    if (opponent_ != NULL) {
        opponent_->hasTurn_ = !hasTurn_;
    }
}


void Player::setName(const std::string& name_)
{
    this->name_ = name_;
}


buildingblocks::engine::internal::Color Player::color() const
{
    return color_;
}

bool Player::hasTurn() const
{
    return hasTurn_;
}

Player* Player::opponent() const
{
    return opponent_;
}

std::string Player::name() const
{
    return name_;
}

void Player::setOpponent(Player *player_)
{
    if (player_ == NULL) {
        return;
    }
    this->opponent_ = player_;
    player_->opponent_ = this;
}

std::ostream& operator<<(std::ostream& ss, const Player& player_)
{
    ss << player_.name();
    return ss;
}

} // namespace internal
} // namespace engine
} // namespace buildingblocks

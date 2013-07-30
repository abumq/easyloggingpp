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

#include "engine/internal/point.hh"
#include "engine/easylogging++.h"

#include <complex>
#include <sstream>

namespace buildingblocks {

namespace engine {

namespace internal {

Point::Point() :
    id_(0),
    x_(0),
    y_(0),
    diameter_(0)
{
}

Point::Point(unsigned int id_, unsigned int x_, unsigned int y_, unsigned int size_) :
    id_(id_),
    x_(x_),
    y_(y_),
    diameter_(size_)
{
}

Point::Point(const Point &point) :
    id_(point.id()),
    x_(point.x()),
    y_(point.y()),
    diameter_(point.diameter())
{
}

Point& Point::operator=(const Point &other)
{
    id_ = other.id();
    x_ = other.x();
    y_ = other.y();
    diameter_ = other.diameter();
    return *this;
}

Point::~Point(void) {

}

bool Point::operator==(const Point& other)
{
    unsigned int distance1_ = distance(other);
    unsigned int distance2_ = other.distance(*this);
    return distance1_ <= diameter() || distance2_ <= other.diameter();
}

unsigned int Point::distance(const Point &other) const
{
    int dist = static_cast<int>(sqrt(pow((other.x() - x()), 2) + pow((other.y() - y()), 2)));
    if (dist < 0) {
        return static_cast<int>(sqrt(pow((x() - other.x()), 2) + pow((y() - other.y()), 2)));
    }
    return dist;
}

void Point::setId(unsigned int id_)
{
    this->id_ = id_;
}

unsigned int Point::id(void) const
{
    return id_;
}

unsigned int Point::x(void) const
{
    return x_;
}

unsigned int Point::y(void) const
{
    return y_;
}

unsigned int Point::diameter(void) const
{
    return diameter_;
}

void Point::setX(unsigned int newX)
{
    x_ = newX;
}

void Point::setY(unsigned int newY)
{
    y_ = newY;
}

void Point::reset(unsigned int newX, unsigned int newY)
{
    setX(newX);
    setY(newY);
}

std::ostream& operator<<(std::ostream& ss, const Point& point_) {
    ss << "[" << point_.x() << ", " << point_.y() << "]";
    return ss;
}
} // namespace internal
} // namespace engine
} // namespace buildingblocks

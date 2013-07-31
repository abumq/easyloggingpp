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

#include "engine/internal/line.hh"
#include "engine/internal/point.hh"

#include <sstream>

namespace buildingblocks {

namespace engine {

namespace internal {

Line::Line(const buildingblocks::engine::internal::Point *const point1, const buildingblocks::engine::internal::Point *const point2)
{
    points_[0] = point1;
    points_[1] = point2;
}

Line::~Line(void)
{
}

bool Line::operator==(const Line &other) const
{
    return  (points_[0]->x() == other.points_[0]->x() && points_[0]->y() == other.points_[0]->y()) &&
            (points_[1]->x() == other.points_[1]->x() && points_[1]->y() == other.points_[1]->y());
}

unsigned int Line::distance(const Line *other) const
{
    unsigned int c1 = other->end()->x() - end()->x();
    unsigned int c2 = other->end()->y() - end()->y();
    return (c1 * c1) + (c2 * c2);
}

const buildingblocks::engine::internal::Point *Line::start(void) const
{
    return points_[0];
}

const buildingblocks::engine::internal::Point *Line::end(void) const
{
    return points_[1];
}

bool Line::isHorizontal(void) const
{
    return start()->y() - end()->y() == 0;
}

bool Line::isVertical(void) const
{
    return  start()->x() - end()->x() == 0;
}

std::ostream& operator<<(std::ostream& ss, const Line& line_)
{
    ss << "[" << line_.points_[0] << ", " << line_.points_[1] << "]";
    return ss;
}

} // namespace internal
} // namespace engine
} // namespace buildingblocks

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

#ifndef BUILDING_BLOCKS_ENGINE_LINE_HH
#define BUILDING_BLOCKS_ENGINE_LINE_HH

#include "engine/internal/point.hh"

#include <complex>
#include <string>

namespace buildingblocks {

namespace engine {

namespace internal {

class Point;

class Line
{
public:
    static const int kMaxPoints = 2;
    explicit Line(const buildingblocks::engine::internal::Point* const point1, const buildingblocks::engine::internal::Point* const point2);
    virtual ~Line(void);
    bool operator==(const Line& other) const;
    unsigned int distance(const Line* other) const;
    const buildingblocks::engine::internal::Point* start(void) const;
    const buildingblocks::engine::internal::Point* end(void) const;
    bool isHorizontal(void) const;
    bool isVertical(void) const;
    friend std::ostream& operator<<(std::ostream& ss, const Line& list_);
private:
    const buildingblocks::engine::internal::Point* points_[kMaxPoints];
};

class LinePredicate {
public:
    explicit LinePredicate(const Line& line_) :
        line_(line_){
    }
    bool operator()(Line* inLine_) {
        return *inLine_ == line_;
    }

private:
    Line line_;
};
} // namespace internal
} // namespace engine
} // namespace buildingblocks
#endif // BUILDING_BLOCKS_ENGINE_LINE_HH

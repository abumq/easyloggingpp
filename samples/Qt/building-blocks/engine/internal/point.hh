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

#ifndef BUILDING_BLOCKS_ENGINE_POINT_HH
#define BUILDING_BLOCKS_ENGINE_POINT_HH

#include <string>

namespace buildingblocks {

namespace engine {

namespace internal {

class Point
{
public:
    explicit Point(void);
    explicit Point(unsigned int id_, unsigned int x_, unsigned int y_, unsigned int diameter_ = 10);
    explicit Point(const Point& other);
    Point& operator=(const Point& other);
    virtual ~Point(void);

    bool operator==(const Point& other);
    unsigned int distance(const Point& other) const;

    unsigned int x(void) const;
    unsigned int y(void) const;
    unsigned int diameter(void) const;
    unsigned int id(void) const;
    void setX(unsigned int newX);
    void setY(unsigned int newY);
    void setId(unsigned int id_);
    void reset(unsigned int newX, unsigned int newY);
    friend std::ostream& operator<<(std::ostream& ss, const Point& point_);

private:
    unsigned int id_;
    unsigned int x_;
    unsigned int y_;
    unsigned int diameter_;
};

class PointPredicate {
public:
    explicit PointPredicate(const Point& point_) :
        point(point_) {
    }

    bool operator()(Point* inPoint) {
        return *inPoint == point;
    }
private:
    Point point;
};
} // namespace internal
} // namespace engine
} // namespace buildingblocks

#endif // BUILDING_BLOCKS_ENGINE_POINT_HH

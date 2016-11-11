#include "point.h"
#include "integer.h"

void PointMakeEmpty(Point *point) {
    point->x = 0;
    point->y = 0;
}

void PointMake(Point *point, uint x, uint y) {
    point->x = x;
    point->y = y;
}

Point PointCreateEmpty() {
    Point point;
    PointMakeEmpty(&point);
    return point;
}

Point PointCreate(uint x, uint y) {
    Point point;
    PointMake(&point, x, y);
    return point;
}

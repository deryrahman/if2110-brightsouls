#ifndef _H_POINT
#define _H_POINT

typedef struct {
    uint x;
    uint y;
} Point;

void PointMakeEmpty(Point *point);
void PointMake(Point *point, uint x, uint y);

Point PointCreateEmpty();
Point PointCreate(uint x, uint y);

#endif

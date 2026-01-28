#pragma once

#include <stddef.h>

typedef struct {
    int x, y;
} Point;

float distance(Point p1, Point p2);
int cmp_point_x(const void *a, const void *b);
int cmp_point_y(const void *a, const void *b);

typedef struct {
    Point *data;
    size_t length;
} Points;

Points generate_points(size_t count, int range);
Points copy_points(const Points *src);
void destroy_points(Points *points);

typedef struct {
    Point l, r;
} Pair;
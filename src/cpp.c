#include "cpp.h"

#include <math.h>
#include <stdlib.h>
#include <string.h>

float distance(Point p1, Point p2) {
    float dx = (float)p1.x - p2.x;
    float dy = (float)p1.y - p2.y;
    return sqrtf(dx * dx + dy * dy);
}

int cmp_point_x(const void *a, const void *b) {
    const Point *p1 = (const Point *)a;
    const Point *p2 = (const Point *)b;

    return p1->x - p2->x;
}

int cmp_point_y(const void *a, const void *b) {
    const Point *p1 = (const Point *)a;
    const Point *p2 = (const Point *)b;

    return p1->y - p2->y;
}

Points generate_points(size_t count, int range) {
    Points points = {.data = (Point *)malloc(count * sizeof(Point)),
                     .length = count};
    memset(points.data, 0, count * sizeof(Point));

    for (size_t i = 0; i < count; ++i) {
        Point point = {.x = rand() % range, .y = rand() % range};
        points.data[i] = point;
    }

    return points;
}

Points copy_points(const Points *src) {
    Points dst;
    dst.length = src->length;
    dst.data = malloc(dst.length * sizeof(Point));

    if (!dst.data) {
        dst.length = 0;
        return dst;
    }

    memcpy(dst.data, src->data, dst.length * sizeof(Point));
    return dst;
}

void destroy_points(Points *points) {
    free(points->data);
    points->data = NULL;
    points->length = 0;
}
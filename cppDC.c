/*
 * Author: Hakan Vardar
 * Date:   2026-01-28
 */

#include "cpp.h"

#include <assert.h>
#include <limits.h>
#include <math.h>
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define RANGE 1000

Pair cppAP(Points points) {
    assert(points.length >= 2 && "Points size must be > 2");

    Pair result = {0};

    float smallest = INFINITY;
    for (size_t i = 0; i < points.length - 1; ++i) {
        for (size_t j = i + 1; j < points.length; ++j) {
            float d = distance(points.data[i], points.data[j]);
            if (d < smallest) {
                smallest = d;
                result.l = points.data[i];
                result.r = points.data[j];
            }
        }
    }

    return result;
}

void split_y(Point mid, const Points y, Points *y_l, Points *y_r) {
    y_l->data = (Point *)malloc(y.length * sizeof(Point));
    y_r->data = (Point *)malloc(y.length * sizeof(Point));
    y_l->length = 0;
    y_r->length = 0;

    for (size_t i = 0; i < y.length; ++i) {
        Point point = y.data[i];
        if (point.x <= mid.x) {
            y_l->data[y_l->length++] = point;
        } else {
            y_r->data[y_r->length++] = point;
        }
    }
};

Pair _cppDC(Points x, int first, int last, Points y) {
    int n = last - first + 1;
    if (n <= 3) {
        Points small;
        small.length = n;
        small.data = &x.data[first];

        return cppAP(small);
    }

    int m = (first + last) / 2;
    Point mid = x.data[m];

    Points y_l;
    Points y_r;
    split_y(mid, y, &y_l, &y_r);

    Pair cpp_l = _cppDC(x, first, m, y_l);
    float dl = distance(cpp_l.l, cpp_l.r);
    Pair cpp_r = _cppDC(x, m + 1, last, y_r);
    float dr = distance(cpp_r.l, cpp_r.r);

    Pair result = {0};
    float smallest = INFINITY;

    if (dl < dr) {
        smallest = dl;
        result = cpp_l;
    } else {
        smallest = dr;
        result = cpp_r;
    }

    Points strip;
    strip.data = malloc(y.length * sizeof(Point));
    strip.length = 0;

    for (size_t i = 0; i < y.length; ++i) {
        if (fabs((float)y.data[i].x - mid.x) <= smallest)
            strip.data[strip.length++] = y.data[i];
    }

    for (size_t i = 0; i < strip.length; ++i) {
        for (size_t j = i + 1;
             j < strip.length && (strip.data[j].y - strip.data[i].y) < smallest;
             ++j) {

            float d = distance(strip.data[i], strip.data[j]);
            if (d < smallest) {
                smallest = d;
                result.l = strip.data[i];
                result.r = strip.data[j];
            }
        }
    }

    return result;
}

Pair cppDC(Points points) {
    assert(points.length >= 2);

    Points p_x = copy_points(&points);
    Points p_y = copy_points(&points);

    qsort(p_x.data, p_x.length, sizeof(Point), cmp_point_x);
    qsort(p_y.data, p_y.length, sizeof(Point), cmp_point_y);

    Pair result = _cppDC(p_x, 0, points.length - 1, p_y);

    destroy_points(&p_x);
    destroy_points(&p_y);

    return result;
}

int main(void) {
    srand(time(NULL));
    Points points = generate_points(10, RANGE);
    Pair cpp = cppDC(points);

    printf("Closest Pair of Points: %d %d | %d %d\n", cpp.l.x, cpp.l.y, cpp.r.x,
           cpp.r.y);

    destroy_points(&points);
    return 0;
}
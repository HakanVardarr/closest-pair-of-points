/*
 * Author: Hakan Vardar
 * Date:   2026-01-28
 */

#include "cppDC.h"
#include "cppAP.h"

#include <assert.h>
#include <limits.h>
#include <math.h>
#include <stddef.h>
#include <stdlib.h>

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

    free(strip.data);
    free(y_l.data);
    free(y_r.data);

    return result;
}

Pair cppDC(Points points) {
    assert(points.length >= 2);

    Points p_x = copy_points(&points);
    Points p_y = copy_points(&points);

    qsort(p_x.data, p_x.length, sizeof(Point), cmp_point_x);
    qsort(p_y.data, p_y.length, sizeof(Point), cmp_point_y);

    Pair result = _cppDC(p_x, 0, points.length, p_y);

    destroy_points(&p_x);
    destroy_points(&p_y);

    return result;
}

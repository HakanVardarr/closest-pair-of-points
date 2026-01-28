/*
 * Author: Hakan Vardar
 * Date:   2026-01-28
 */

#include "cppAP.h"

#include <assert.h>
#include <limits.h>
#include <math.h>
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define RANGE 1000

/*
    cppAP - Closest Pair of Points (Comparing All Pairs)

    The straightforward algorithm cppAP compares all (n 2) pairs of points with
   each other and takes O(n^2) time.

    This function requires the length of points to be greater than 2
*/
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

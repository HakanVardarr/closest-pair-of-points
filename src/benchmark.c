#define _POSIX_C_SOURCE 200809L

#include "cpp.h"
#include "cppAP.h"
#include "cppDC.h"

#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define RANGE 10000000
#define NPOINTS 10000

double now_seconds(void) {
    struct timespec ts;
    clock_gettime(CLOCK_MONOTONIC, &ts);
    return ts.tv_sec + ts.tv_nsec * 1e-9;
}

int main(void) {
    srand((unsigned)time(NULL));

    printf("Generating %d points...\n", NPOINTS);
    Points points = generate_points(NPOINTS, RANGE);

    printf("Running cppAP...\n");
    double t1 = now_seconds();
    Pair ap = cppAP(points);
    double t2 = now_seconds();

    float d_ap = distance(ap.l, ap.r);

    printf("cppAP result: (%d,%d) - (%d,%d)\n", ap.l.x, ap.l.y, ap.r.x, ap.r.y);
    printf("cppAP time: %.6f seconds\n\n", t2 - t1);

    printf("Running cppDC...\n");
    double t3 = now_seconds();
    Pair dc = cppDC(points);
    double t4 = now_seconds();

    float d_dc = distance(dc.l, dc.r);

    printf("cppDC result: (%d,%d) - (%d,%d)\n", dc.l.x, dc.l.y, dc.r.x, dc.r.y);
    printf("cppDC time: %.6f seconds\n\n", t4 - t3);

    printf("cppAP distance: %.6f\n", d_ap);
    printf("cppDC distance: %.6f\n", d_dc);

    if (fabsf(d_ap - d_dc) < 1e-6f)
        printf("Results match: TRUE \n");
    else
        printf("Results match: FALSE \n");

    destroy_points(&points);
    return 0;
}

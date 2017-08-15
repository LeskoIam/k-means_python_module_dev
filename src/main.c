
#include <malloc.h>
#include <stdio.h>
#include "main.h"


int main()
{
    double lats[10] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
    double lons[10] = {11, 12, 13, 14, 15, 16, 17, 18, 19, 20};
    struct cluster clusters[3];
    k_means(lats, lons, 10, 3, clusters);
    for (int i = 0; i < 3; i++) {
        printf("#%d:\n    N:%d\n    (%f, %f)\n", i, clusters[i].num_points, clusters[i].center.lat, clusters[i].center.lon);
        free(clusters[i].cluster_points);
    }
}

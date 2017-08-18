#include <stdio.h>
#include <malloc.h>
#include <string.h>
#include <math.h>

#include "../main.h"

// K-Means cutoff jitter distance
#define CUTOFF 0.000001

int k_means(const double *lats, const double *lons, const int N, const int K, struct cluster *clusters)
{
    // K-means implementation
    struct geopoint *points = (struct geopoint *) malloc(sizeof(struct geopoint) * N);
    // Fill the points array
    for (int i = 0; i < N; i++) {
        points[i].lon = *(lons + i);
        points[i].lat = *(lats + i);
    }

    // struct cluster clusters[K];
    int initial_indexes[K];

    // Pick out K random points to use as our initial centroids, well this are actually indexes...
    if (random_sample_index(K, N, initial_indexes) != 0) {
        return -1;
    }
    DEBUG_PRINT("K: %d\n", K);

    // Create K clusters using those centroids
    // printf("Random points to seed first clusters\n");
    for (int i = 0; i < K; i++) {
        clusters[i].center = points[initial_indexes[i]];
        clusters[i].num_points = 1;
    }

    // Loop through the dataset until the clusters stabilize
    double smallest_distance;
    double distance;
    int cluster_index;
    int n_loops = 0;
    int realloc_count = 0;
    int realloc_loop_count = 0;

    struct geopoint **lists;
    lists = malloc2dgeoarray(K, N);
    struct geopoint dummy;
    dummy.lat = -1;
    dummy.lon = -1;

    int inner_index;

    while (1) {
        n_loops++;
        DEBUG_PRINT("Main loop count: %d\n", n_loops);

        for (int i = 0; i < K; ++i) {
            for (int j = 0; j < N; j++) {
                lists[i][j] = dummy;
            }
        }
        inner_index = 0;
        // For every point in the dataset ...
        for (int p = 0; p < N; p++) {
            // Get the distance between that point and the centroid of the first cluster.
            smallest_distance = calculate_geodistance(points[p], clusters[0].center);
            cluster_index = 0;
            DEBUG_PRINT("Smallest distance: %f\n", smallest_distance);
            // For the remainder of the clusters ...
            for (int i = 0; i < K - 1; i++) {
                // calculate the distance of that point to each other cluster's centroid.
                distance = calculate_geodistance(points[p], clusters[i + 1].center);
                DEBUG_PRINT("Distance: %f\n", distance);
                // If it's closer to that cluster's centroid update what we think the smallest distance is,
                // and set the point to belong to that cluster
                if (distance < smallest_distance){
                    smallest_distance = distance;
                    cluster_index = i + 1;
                    DEBUG_PRINT("Cluster_index: %d\n", cluster_index);
                }
            }
            // lists[cluster_index].append(p) in Python translates to ...
            lists[cluster_index][inner_index] =  *(points + p);
            inner_index++;

        }
        // Set our biggest_shift to zero for this iteration
        double biggest_shift = 0.0;
        for (int i = 0; i < K; i++) {
            // Calculate how far the centroid moved in this iteration
            struct geopoint old_center = clusters[i].center;

            // Create temp cluster points and filter out -1 (unused slots in lists array)
            // Count number of valid points
            int count = 0;
            for (int j = 0; j < N; j++) {
                if (lists[i][j].lat != -1) {
                    count++;
                }
            }

            // Fill temp points with valid points
            struct geopoint temp[count];
            int pi = 0;
            for (int p = 0; p < N; p++) {
                if (lists[i][p].lat != -1) {
                    temp[pi] = lists[i][p];
                    pi++;
                }
            }
            // Update cluster
            // Update centroid count
            // Allocate memory for points and copy temp to new address
            DEBUG_PRINT("num_point=%d  count=%d\n", clusters[i].num_points, count);
            if (clusters[i].num_points < count) {
                clusters[i].cluster_points = (struct geopoint *) realloc(clusters[i].cluster_points, sizeof(struct geopoint) * count);
                realloc_count++;
            }
            realloc_loop_count++;
            clusters[i].num_points = count;
            memcpy(clusters[i].cluster_points, temp, sizeof(struct geopoint) * count);
            // Calculate new cluster center and update its center
            double new_center[2];
            struct geopoint new_geocenter;
            calculate_centroid_center(clusters[i], new_center);
            new_geocenter.lat = *(new_center);
            new_geocenter.lon = *(new_center + 1);
            clusters[i].center = new_geocenter;
            // Calculate shift
            double shift;
            shift = calculate_geodistance(old_center, clusters[i].center);

            // Keep track of the largest move from all cluster centroid updates
            biggest_shift = fmax(biggest_shift, shift);
        }
        DEBUG_PRINT("Biggest shift: %f\n", biggest_shift);
        if (biggest_shift < CUTOFF) {
            break;
        }
    }

    // Clean
    free(points);

    for(int i = 0; i < K; i++) {
        free(lists[i]);
    }
    free(lists);

    DEBUG_PRINT("n_loops: %d\nrealloc_loop_count: %d\nrealloc_count: %d\n%f\n", n_loops, realloc_loop_count, realloc_count, (double) realloc_loop_count/(double) realloc_count);

    return 0;
}
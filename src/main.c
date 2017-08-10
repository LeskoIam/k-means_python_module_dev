#include <stdio.h>
#include <malloc.h>
#include <string.h>
#include <math.h>
#include "main.h"

#define MAX_ARR_LEN 12

// K-Means variables
#define N 200
#define K 5
#define CUTOFF 0.0000001

void test_random_sample();
void test_calculate_geodistance();
void test_mean();
void test_calculate_centroid();



int main()
{
//    test_random_sample();
//    test_calculate_geodistance();
//    test_mean();
//    test_calculate_centroid();


    // K-means implementation
    struct geopoint points[N];
    double lats[N] = {16.55, 16.46, 15.4, 11.12, 12.91, 12.4, 14.44, 10.61, 16.06, 10.88, 12.85, 15.14, 13.86, 14.27, 16.87, 10.67, 16.37, 10.69, 13.12, 11.94, 11.0, 15.99, 11.42, 15.06, 16.17, 15.05, 12.6, 16.78, 13.05, 15.77, 11.0, 12.26, 15.22, 12.67, 15.65, 10.13, 16.68, 13.64, 14.58, 10.4, 12.05, 11.66, 14.78, 11.71, 12.73, 12.07, 12.94, 14.87, 11.82, 16.27, 14.46, 14.69, 11.92, 16.63, 14.72, 15.88, 11.75, 13.33, 16.32, 14.65, 12.0, 10.45, 13.74, 10.32, 10.15, 10.91, 11.71, 10.9, 11.92, 16.13, 13.98, 16.89, 12.31, 16.02, 15.26, 12.77, 13.55, 14.76, 15.69, 10.35, 10.97, 12.67, 11.24, 11.68, 16.75, 16.25, 12.91, 14.56, 11.74, 16.76, 14.35, 12.41, 13.88, 11.28, 10.67, 10.96, 16.11, 10.84, 16.85, 13.14, 16.73, 15.93, 14.02, 10.59, 11.1, 11.15, 16.35, 11.31, 16.64, 11.1, 16.98, 15.91, 13.49, 15.49, 10.39, 12.12, 12.92, 14.39, 16.56, 15.07, 10.78, 11.27, 10.58, 15.73, 15.54, 16.32, 10.43, 11.76, 12.39, 12.74, 13.81, 13.56, 14.55, 10.6, 12.63, 12.37, 12.14, 11.75, 15.81, 15.88, 12.74, 15.43, 15.24, 11.95, 12.72, 14.54, 15.12, 14.58, 12.64, 15.03, 11.49, 14.39, 16.5, 11.61, 15.25, 10.84, 13.41, 11.19, 14.65, 13.76, 16.11, 16.9, 15.48, 11.1, 14.68, 14.53, 16.69, 11.21, 13.44, 16.89, 14.09, 12.85, 16.78, 13.13, 11.44, 10.98, 12.62, 15.53, 11.44, 14.26, 15.52, 13.02, 12.51, 14.18, 12.9, 12.89, 14.13, 12.57, 16.19, 15.0, 11.26, 12.04, 12.27, 14.45, 12.14, 14.59, 14.34, 11.05, 13.01, 12.81};
    double lons[N] = {44.3, 46.39, 42.44, 42.69, 45.41, 44.09, 45.63, 41.82, 40.35, 45.14, 46.35, 40.22, 46.13, 42.1, 41.46, 40.63, 46.62, 42.75, 45.05, 40.96, 40.82, 45.53, 46.53, 43.68, 44.66, 46.31, 46.91, 46.42, 46.41, 45.25, 44.21, 40.97, 42.09, 40.66, 44.14, 45.57, 44.86, 46.14, 42.99, 40.89, 46.77, 45.4, 44.05, 41.23, 43.46, 42.39, 43.13, 46.43, 43.07, 44.97, 43.75, 43.0, 44.66, 40.51, 40.71, 42.86, 43.13, 43.27, 45.9, 45.08, 42.91, 44.34, 40.66, 45.67, 46.25, 40.7, 45.51, 46.96, 40.54, 44.28, 40.04, 43.46, 40.95, 43.05, 45.51, 46.42, 46.52, 45.5, 40.03, 40.15, 44.54, 41.51, 43.0, 44.94, 43.85, 42.82, 42.88, 42.8, 40.72, 42.97, 45.23, 45.46, 41.0, 42.81, 46.53, 41.93, 45.73, 44.02, 46.43, 46.12, 45.12, 41.54, 46.39, 43.71, 40.68, 42.55, 46.34, 41.29, 42.76, 46.22, 40.96, 44.44, 41.39, 43.96, 40.97, 41.27, 43.36, 45.11, 41.85, 44.93, 46.77, 46.91, 45.71, 43.21, 45.49, 45.72, 44.13, 41.18, 43.67, 40.6, 45.64, 41.0, 42.04, 45.43, 42.95, 44.21, 43.27, 41.12, 44.79, 40.83, 45.62, 42.78, 46.52, 40.34, 43.15, 43.95, 45.47, 40.69, 45.91, 45.98, 44.41, 43.66, 42.11, 41.14, 44.22, 40.05, 45.85, 43.83, 42.43, 41.35, 44.14, 40.44, 45.78, 46.79, 46.23, 43.26, 45.17, 43.37, 40.82, 43.9, 45.7, 45.81, 45.18, 44.14, 43.5, 45.98, 45.33, 41.5, 45.51, 42.63, 42.87, 41.82, 41.82, 44.23, 41.07, 41.07, 43.67, 43.49, 41.72, 41.66, 44.03, 40.89, 44.28, 45.82, 45.62, 44.78, 41.08, 46.42, 46.09, 43.36};
    // Fill the points array
    for (int i = 0; i < N; i++) {
        points[i].lon = *(lons + i);
        points[i].lat = *(lats + i);
    }

    struct cluster clusters[K];
    int initial_indexes[K];

    // Pick out k random points to use as our initial centroids, well this are actually indexes...
    random_sample_index(K, N, initial_indexes);
    print_int_array(initial_indexes, K);

    // Create k clusters using those centroids
    printf("Random points to seed first clusters\n");
    for (int i = 0; i < 5; i++) {
        clusters[i].center = points[initial_indexes[i]];
        clusters[i].num_points = 1;
        clusters[i].cluster_points = (struct geopoint *) malloc(sizeof(struct geopoint));
        // print_cluster(clusters[i]);
}

    // Loop through the dataset until the clusters stabilize
    double smallest_distance;
    double distance;
    int cluster_index;
    int n_loops = 0;
    while (1) {
        n_loops++;
        printf("\n");

        struct geopoint lists[K][N];
        struct geopoint dummy;
        dummy.lat = -1;
        dummy.lon = -1;
        for (int i = 0; i < K; ++i) {
            for (int j = 0; j < N; j++) {
                lists[i][j] = dummy;
            }
        }
        int inner_index = 0;
        // For every point in the dataset ...
        for (int p = 0; p < N; p++) {
            // Get the distance between that point and the centroid of the first cluster.
            smallest_distance = calculate_geodistance(points[p], clusters[0].center);
            cluster_index = 0;
            // printf("smallest distance: %f\n", smallest_distance);
            // For the remainder of the clusters ...
            for (int i = 0; i < K - 1; i++) {
                // calculate the distance of that point to each other cluster's centroid.
                // distance = get_distance(p, clusters[p + 1].centroid)
                distance = calculate_geodistance(points[p], clusters[i + 1].center);
                // printf("distance: %f\n", distance);
                // If it's closer to that cluster's centroid update what we
                // think the smallest distance is, and set the point to belong
                // to that cluster
                if (distance < smallest_distance){
                    smallest_distance = distance;
                    cluster_index = i + 1;
                    // printf("cluster_index: %d\n", cluster_index);
                }

            }
            // lists[cluster_index].append(p)
            lists[cluster_index][inner_index] = points[p];
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
            printf("Count of points: %d\n", count);

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
            clusters[i].num_points = count;
            // Allocate memory for points and copy temp to new address
            clusters[i].cluster_points = (struct geopoint *) realloc(clusters[i].cluster_points, sizeof(struct geopoint) * count);
            memcpy(clusters[i].cluster_points, temp, sizeof(struct geopoint)*count);
            // Calculate new cluster center and update its center
            double new_center[2];
            struct geopoint new_geocenter;
            calculate_centroid_center(clusters[i], new_center);
            new_geocenter.lat = new_center[0];
            new_geocenter.lon = new_center[1];
            clusters[i].center = new_geocenter;
            // Calculate shift
            double shift;
            shift = calculate_geodistance(old_center, clusters[i].center);

            // Keep track of the largest move from all cluster centroid updates
            biggest_shift = fmax(biggest_shift, shift);
        }
        printf("Biggest shift: %f\n", biggest_shift);
        if (biggest_shift < CUTOFF) {
            break;
        }
    }
    
    // Clean
    for (int c = 0; c < K; c++) {
        print_cluster(clusters[c]);
        free(clusters[c].cluster_points);
    }
    printf("n_loops: %d", n_loops);

    return 0;
}

void test_random_sample()
{
    printf("\n---- Test random_sample ----\n");
    int ret_code = 0;

    const int k = 4;
    double arr_in[MAX_ARR_LEN] = {1.12, 2.23, 3.34, 4.45,
                                  6.67, 15.1516, 20.2021, 36.2637,
                                  78.7879, 1.12, 5.56, 12.1213};
    double random_points[k];
    ret_code = random_sample(k, arr_in, MAX_ARR_LEN, random_points);

    print_double_array(random_points, k);
    printf("ret_code: %d\n---- #### ----\n", ret_code);
}


void test_calculate_geodistance()
{
    printf("\n---- Test calculate_geodistance ----\n");
    int ret_code = 0;

    struct geopoint p1, p2;
    p1.lat = 1.12, p1.lon = 2.23;
    p2.lat = 12.12213, p2.lon = 1.12556;
    double distance;

    distance = calculate_geodistance(p1, p2);
    printf("Distance between points is: %f\n", distance);

    printf("ret_code: %d\n---- #### ----\n", ret_code);
}

void test_mean()
{
    printf("\n---- Test mean ----\n");
    int ret_code = 0;

    double arr_in[6] = {1.12, 1.13, 1.14, 2.15, 1.16, 1.17};
    double m;

    m = mean(arr_in, 6);
    printf("Mean: %f\n", m);

    printf("ret_code: %d\n---- #### ----\n", ret_code);
}


void test_calculate_centroid()
{
    printf("\n---- Test calculate_centroid_center ----\n");
    int ret_code = 0;

    struct geopoint gcenter;
    gcenter.lat = 0.;
    gcenter.lon = 0.;

    struct geopoint p1, p2, p3;
    p1.lat = 13., p1.lon = 2.;
    p2.lat = 12., p2.lon = 2.;
    p3.lat = 14., p3.lon = 2.;

    static struct geopoint cpoints[3];
    cpoints[0] = p1;
    cpoints[1] = p2;
    cpoints[2] = p3;

    struct cluster test_cluster;
    test_cluster.num_points = 3;
    test_cluster.center = gcenter;
    test_cluster.cluster_points = cpoints;

    printf("Cluster before centroid calculation\n");
    print_cluster(test_cluster);

    double center[2];
    calculate_centroid_center(test_cluster, center);
    test_cluster.center.lat = center[0];
    test_cluster.center.lon = center[1];

    printf("Cluster after center calculation\n");
    print_cluster(test_cluster);

    printf("ret_code: %d\n---- #### ----\n", ret_code);
}
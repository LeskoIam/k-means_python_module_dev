#include <stdio.h>
#include "main.h"

#define MAX_ARR_LEN 12

// K-Means variables
#define N 20
#define K 5

void test_random_sample();
void test_calculate_geodistance();
void test_mean();
void test_calculate_centroid();



int main()
{
    test_random_sample();
    test_calculate_geodistance();
    test_mean();
    test_calculate_centroid();


    // K-means implementation
    struct geopoint points[N];
    double lats[N] = {16.32, 16.99, 15.94, 16.45, 12.86, 14.64, 11.92, 12.69, 11.81, 12.83,
                       10.76, 14.94, 16.59, 16.68, 15.97, 10.0, 15.76, 14.06, 13.49, 12.36};
    double lons[N] = {44.07, 42.37, 40.26, 42.26, 43.54, 40.76, 45.14, 44.78, 42.27, 43.94,
                       41.06, 46.98, 44.32, 40.05, 41.57, 46.65, 41.13, 46.82, 43.71, 40.6};
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
        clusters[i].cluster_points = &points[initial_indexes[i]]; // This is 'dummy' data, khmmm...
        // print_cluster(clusters[i]);
}

    // Loop through the dataset until the clusters stabilize
    double smallest_distance;
    double distance;
    int cluster_index;
    while (1) {
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
            printf("smallest distance: %f\n", smallest_distance);
            // For the remainder of the clusters ...
            for (int i = 0; i < K - 1; i++) {
                // calculate the distance of that point to each other cluster's centroid.
                // distance = get_distance(p, clusters[p + 1].centroid)
                distance = calculate_geodistance(points[p], clusters[i + 1].center);
                printf("distance: %f\n", distance);
                // If it's closer to that cluster's centroid update what we
                // think the smallest distance is, and set the point to belong
                // to that cluster
                if (distance < smallest_distance){
                    smallest_distance = distance;
                    cluster_index = i + 1;
                    printf("cluster_index: %d\n", cluster_index);
                }

            }
            // lists[cluster_index].append(p)
            lists[cluster_index][inner_index] = points[p];
//            printf("lists[%d].append({%f, %f})\n", cluster_index, points[p].lat, points[p].lon);
//            printf("inner_index: %d\n", inner_index);
            inner_index++;

        }
        // Set our biggest_shift to zero for this iteration
        double biggest_shift = 0.0;
        for (int i = 0; i < K; i++) {
            // Calculate how far the centroid moved in this iteration
            struct geopoint old_center = clusters[i].center;
            // Create temp cluster points and filter out -1 (unused slots in lists array)
            // clusters[i].cluster_points =
        }
        break;
    }
    

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
    ret_code = random_sample(k, arr_in, MAX_ARR_LEN, &random_points);

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

    struct geopoint cpoints[3];
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
#include <stdio.h>
#include "main.h"

#define MAX_ARR_LEN 12


void test_random_sample();
void test_calculate_distance();
void test_mean();
void test_calculate_centroid();



int main()
{
    test_random_sample();
    test_calculate_distance();
    test_mean();
    test_calculate_centroid();

    return 0;
}

void test_random_sample()
{
    printf("\n---- Test random_sample ----\n");
    int ret_code = 0;

    const int K = 4;
    double arr_in[MAX_ARR_LEN] = {1.12, 2.23, 3.34, 4.45,
                                  6.67, 15.1516, 20.2021, 36.2637,
                                  78.7879, 1.12, 5.56, 12.1213};
    double random_points[K];
    ret_code = random_sample(K, arr_in, MAX_ARR_LEN, random_points);

    print_double_array(random_points, K);
    printf("ret_code: %d\n---- #### ----\n", ret_code);
}


void test_calculate_distance()
{
    printf("\n---- Test calculate_distance ----\n");
    int ret_code = 0;

    double p1[3] = {1., 2., -3.};
    double p2[3] = {1., 3., -3.};
    double distance;

    distance = calculate_distance(p1, p2, 3);
    printf("Distance between points is: %f\n", distance);

    printf("ret_code: %d\n---- #### ----\n", ret_code);
}

void test_mean()
{
    printf("\n---- Test mean ----\n");
    int ret_code = 0;

    double arr_in[6] = {1.12, 1.13, 1.14, 1.15, 1.16, 1.17};
    double m;

    m = mean(arr_in, 6);
    printf("Mean: %f\n", m);

    printf("ret_code: %d\n---- #### ----\n", ret_code);
}


void test_calculate_centroid()
{
    printf("\n---- Test calculate_centroid ----\n");
    int ret_code = 0;

    struct geopoint gcenter;
    gcenter.lat = 0.;
    gcenter.lon = 0.;

    struct geopoint p1, p2, p3;
    p1.lat = 13., p2.lat = 12., p3.lat = 14.;
    p1.lon = 2., p2.lon = 1., p3.lon = 2.;

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
    calculate_centroid(test_cluster, center);
    test_cluster.center.lat = center[0];
    test_cluster.center.lon = center[1];

    printf("Cluster after centroid calculation\n");
    print_cluster(test_cluster);

    printf("ret_code: %d\n---- #### ----\n", ret_code);
}
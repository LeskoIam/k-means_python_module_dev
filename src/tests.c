//
// Created by User on 11. 08. 2017.
//

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
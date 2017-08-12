//
// Created by User on 6. 08. 2017.
//

struct geopoint
{
    double lat;  // 8
    double lon;  // 8
};


struct cluster  // 32
{
    int num_points;          // 4
    struct geopoint center;  // 16
    struct geopoint *cluster_points;
};

int k_means(const double *lats, const double *lons, int N, int K);
int in_int_array(int number, const int *arr, int arr_len);
void print_int_array(const int *arr, int arr_len);
void print_double_array(const double *arr, int arr_len);
double calculate_geodistance(struct geopoint p1, struct geopoint p2);
double calculate_distance(const double *p1, const double *p2, int dim);
void calculate_centroid_center(struct cluster cl, double *buf);
void print_cluster(struct cluster cl);
double mean(const double *arr, int arr_len);
int random_sample(int k, double *arr, int arr_len, double *buf);
int random_sample_index(int k, int arr_len, int *buf);
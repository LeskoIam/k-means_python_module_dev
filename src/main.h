//
// Created by User on 6. 08. 2017.
//

struct geopoint
{
    double lat;
    double lon;
};


struct cluster
{
    int num_points;
    struct geopoint center;
    struct geopoint *cluster_points;
};

double max_double(double a, double b);
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
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

int in_int_array(int number, int *arr, int arr_len);
void print_int_array(int *arr, int arr_len);
void print_double_array(double *arr, int arr_len);
double calculate_distance(double *p1, double *p2, int dim);
void calculate_centroid(struct cluster cl, double *buf);
void print_cluster(struct cluster cl);
double mean(double *arr, int arr_len);
int random_sample(int k, double *arr, int arr_len, double *buf);

//
// Created by User on 6. 08. 2017.
//

#ifdef DEBUG
#define DEBUG_TEST 1
#else
#define DEBUG_TEST 0
#endif
#define DEBUG_PRINT(fmt, args...) \
        do { if (DEBUG_TEST) fprintf(stderr, "%s:%d:%s(): " fmt, __FILE__, \
                                __LINE__, __FUNCTION__, ##args); } while (0)


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

struct geopoint **malloc2dgeoarray(int K, int N);
int k_means(const double *lats, const double *lons, int N, int K, struct cluster *clusters);
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
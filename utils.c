#include <time.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include "main.h"


#define sqr(x) ((x)*(x))


/** \brief Check if integer is in array
 *
 * \param number int - number to check for
 * \param arr int* - array in which to check for presence of a number
 * \param arr_len int - length of array
 * \return int - 1 if found, 0 if not found
 */
int in_int_array(int number, int *arr, int arr_len)
{
    for (int i=0; i < arr_len; i++)
    {
        if (*(arr+i) == number)
            return 1;
    }
    return 0;
}


/** \brief Print int array as "int{....}"
 *
 * \param arr int* - array to print
 * \param arr_len int - length of array
 */
void print_int_array(int *arr, int arr_len)
{
    printf("int{");
    int i = 0;
    for (i; i < arr_len; i++)
    {
        printf("%d", *(arr+i));
        if (i < arr_len-1)
            printf(", ");
    }
    printf("}\n");
}


/** \brief Print double array as "double{....}"
 *
 * \param arr int* - array to print
 * \param arr_len int - length of array
 */
void print_double_array(double *arr, int arr_len)
{
    printf("double{");
    int i = 0;
    for (i; i < arr_len; i++)
    {
        printf("%f", *(arr+i));
        if (i < arr_len-1)
            printf(", ");
    }
    printf("}\n");
}


/** \brief Calculate euclidean distance between two N dimensional points
 *
 * \param p1 double* - first point
 * \param p2 double* - second point
 * \param dim int - number of dimensions points have
 * \return double - distance
 */
double calculate_distance(double *p1, double *p2, int dim)
{
    double distance_sq_sum = 0;

    for (int i = 0; i < dim; i++)
    {
        distance_sq_sum += sqr(*(p1 + i) - *(p2 + i));
    }

    return distance_sq_sum;
}


/** \brief Calculate center point of centroid
 *
 * \param cl struct cluster - cluster structure
 * \param buf - buffer for result
 * \return double - center point of cluster
 */
void calculate_centroid(struct cluster cl, double *buf)
{
    double lat_coords[cl.num_points];
    double lon_coords[cl.num_points];

    for (int i = 0; i < cl.num_points; i++)
    {
        *(lat_coords + i) = cl.cluster_points[i].lat;
        *(lon_coords + i) = cl.cluster_points[i].lon;
    }

    double m_lat = mean(lat_coords, cl.num_points);
    double m_lon = mean(lon_coords, cl.num_points);

    // printf("mlat: %f, mlon: %f\n", m_lat, m_lon);
    *buf = m_lat;
    *(buf + 1) = m_lon;
}


void print_cluster(struct cluster cl)
{
    printf("cluster{\n"
                   "    center lat: %f\n"
                   "    center lon; %f\n"
                   "    num_points: %d\n"
                   "    cluster_points:\n"
                   "        {",
           cl.center.lat,
           cl.center.lon,
           cl.num_points);
    for (int i = 0; i < cl.num_points; i++)
    {
        printf("{%f, %f}",
               cl.cluster_points[i].lat,
               cl.cluster_points[i].lon);
        if (i < cl.num_points-1)
            printf(", ");
    }
    printf("}\n");
}


/** \brief Calculate mean of given array
 *
 * \param arr double* - array to calculate mean for
 * \param arr_len int - length of array
 * \return double - mean
 */
double mean(double *arr, int arr_len)
{
    double sum = 0;
    for (int i = 0; i < arr_len; i++)
    {
        sum += *(arr + i);
    }
    return sum/(double) arr_len;
}


/** \brief Select k random elements and fill buf with them, from array arr of length arr_len
 *
 * \param k int - number of elements to select
 * \param arr double* - array from which to select
 * \param arr_len int - length of array
 * \param buf double* - array to which selected numbers are stored
 * \return int - 0 if OK, -1 if errors
 */
int random_sample(int k, double *arr, int arr_len, double *buf)
{
    // Check if k exceeds length of array (arr_len)
    if (k > arr_len || k < 1)
    {
        printf("ERROR: k > arr_len || k < 1, ABORTING\n");
        return -1;
    }
    if (k == arr_len)
    {
        printf("WARNING: k == arr_len, COPYING ORIGINAL ARRAY\n");
        // memcpy(dest, src, sizeof(src));
        memcpy(buf, arr, sizeof(double)*k);
        return 0;
    }

    int used_indexes[k];  // already used indexes
    int random_index;
    // Fill with value of arr_len, maximum index is, of course, arr_len - 1
    // so this should be OK
    for (int i=0; i<k; i++) {used_indexes[i] = arr_len;}

    srand((unsigned) time(NULL));  // Initialize random seed

    int i = 0;
    while (i < k)
    {
        random_index = rand() % arr_len;  // between 0 and arr_len - 1
        // printf("Loop random index: %d\n", random_index);

        // Check if this index was already selected
        if (in_int_array(random_index, used_indexes, k) == 1)
        {
            // printf("INFO: index %d already selected\n", random_index);
            continue;
        }
        *(used_indexes + i) = random_index;
        *(buf + i) = *(arr + random_index);

        print_int_array(used_indexes, k);
        i++;
    }

    return 0;
}

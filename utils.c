#include <time.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>


/** \brief Check if integer is in array
 *
 * \param number int - number to check for
 * \param arr int* - array in which to check for presence of a number
 * \param arr_len int - length of array
 * \return int - 1 if found, 0 if not found
 *
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


void print_int_array(int *arr, int arr_len) {
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


/** \brief Select k random elements and fill buf with them, from array arr of length arr_len
 *
 * \param k int - number of elements to select
 * \param arr double* - array from which to select
 * \param arr_len int - length of array
 * \param buf double* - array to which selected numbers are stored
 * \return int - 0 if OK, -1 if errors
 *
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

    srand(time(NULL));  // Initialize random seed

    int i = 0;
    while (i < k)
    {
        random_index = rand() % arr_len;  // between 0 and arr_len - 1
        // printf("Loop random index: %d\n", random_index);

        // Check if this index was already selected
        if (in_int_array(random_index, used_indexes, k) == 1)
        {
            // printf("Index already selected: %d\n", random_index);
            continue;
        }
        used_indexes[i] = random_index;
        *(buf + i) = *(arr + random_index);

        print_int_array(used_indexes, k);
        i++;
    }

    return 0;
}

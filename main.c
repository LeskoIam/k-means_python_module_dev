#define MAX_ARR_LEN 12

void print_double_array(double *arr, int arr_len);
int random_sample(int k, double *arr, int arr_len, double *buf);

int main()
{
    const int K = 6;
    double arr_in[MAX_ARR_LEN] = {1.12, 2.23, 3.34, 4.45,
                                  6.67, 15.1516, 20.2021, 36.2637,
                                  78.7879, 1.12, 5.56, 12.1213};
    double random_points[K];
    int ret_code = random_sample(K, arr_in, MAX_ARR_LEN, random_points);

    print_double_array(random_points, K);

    return ret_code;
}

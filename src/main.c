
#include <malloc.h>
#include <stdio.h>
#include "main.h"


int main()
{
    double lats[10] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
    double lons[10] = {11, 12, 13, 14, 15, 16, 17, 18, 19, 20};
    k_means(lats, lons, 20, 5);

    // char a[10][20]
    struct geopoint **a;
    struct geopoint testp;
    testp.lat = 0.1;
    testp.lon = 1.2;

    int K = 5000;
    int N = 200000;
    a = malloc2dgeoarray(K, N);

    a[0][0] = testp;
    printf("%f\n", a[0][0].lat);


    for(int i = 0; i < K; i++) {
        free(a[i]);
    }
    free(a);
}

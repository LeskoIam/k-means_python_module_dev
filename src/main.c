
#include "main.h"

int main()
{
    double lats[10] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
    double lons[10] = {11, 12, 13, 14, 15, 16, 17, 18, 19, 20};
    k_means(lats, lons, 20, 5);

    struct geopoint lists[32][4000];

}
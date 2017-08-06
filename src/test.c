//
// Created by User on 6. 08. 2017.
//

#define sqr(x) ((x)*(x))

double calculate_distance(double *p1, double *p2, int dim)
{
    double distance_sq_sum = 0;

    for (int i = 0; i < dim; i++)
    {
        distance_sq_sum += sqr(*(p1 + i) - *(p2 + i));
    }

    return distance_sq_sum;
}
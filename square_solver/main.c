#include "square_solver.h"


int main()
{
    double a = 0, b = 0, c = 0;
    printf("Enter coefficients: a, b, c\n");
    scanf("%lf\n%lf\n%lf", &a, &b, &c);

    solve_square_equasion(a, b, c);
}
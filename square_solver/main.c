#include "square_solver.h"

int main()
{   

    double a = NAN, b = NAN, c = NAN, x1 = NAN, x2 = NAN;
    int result_code = 0;

    printf("Enter coefficients: a, b, c\n");
    scanf("%lf\n%lf\n%lf", &a, &b, &c);

    result_code = solve_square_equasion(a, b, c, &x1, &x2);
    print_solutions(result_code, x1, x2);
}
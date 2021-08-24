#include "square_solver.h"


int solve_square_equasion(double a, double b, double c, double* x1, double* x2)
{   
    assert(!isnan(a) && isfinite(a));
    assert(!isnan(b) && isfinite(b));
    assert(!isnan(c) && isfinite(c));

    if (fabs(a) < epsilon)
    {
        if (b == 0)
        {
            if (c == 0)
            {   
                return INFINITY_NUMBER_OF_SOLUTIONS;
            }

            return NO_REAL_SOLUTIONS;
        }

        *x1 = *x2 = -c / b;
        return ONE_SOLUTION;
    }

    double D = b*b - 4*a*c;

    if (fabs(D) < epsilon)
    {   
        *x1 = *x2 = -b / (2 * a);
        return ONE_SOLUTION;
    }

    if (D < 0)
    {   
        return NO_REAL_SOLUTIONS;
    }

    
    
    *x1 = (-b + sqrt (D)) / (2 * a);
    *x2 = (-b - sqrt (D)) / (2 * a);

    return TWO_SOLUTIONS;
}

//flexxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

void print_solutions(int result_code, double x1, double x2)
{
    switch (result_code)
    {
        case INFINITY_NUMBER_OF_SOLUTIONS:
            printf("There're infinity number of solutions\n");
            break;
        
        case NO_REAL_SOLUTIONS:
            printf("There're no real solutions\n");
            break;
        
        case ONE_SOLUTION:
            printf("There's only one solution: x=%lf\n", x1);
            break;
        
        case TWO_SOLUTIONS:
            printf("Solutions: x1=%lf x2=%lf\n", x1, x2);
            break;
        
        default:
            break;
    }
}

//flexxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

void unit_test()
{   
    int result_code = 0;
    double x1=NAN, x2=NAN;


    printf("\na = 0, b = 1, c = 2\nCorrect: Error\n");
    result_code = solve_square_equasion(0, 1, 2, &x1, &x2);
    print_solutions(result_code, x1, x2);

    printf("\na = 1, b = 2, c = 1\nCorrect: x=-1\n");
    result_code = solve_square_equasion(1, 2, 1, &x1, &x2);
    print_solutions(result_code, x1, x2);

    printf("\na = 1, b = -2, c = 1\nCorrect: x=1\n");
    result_code = solve_square_equasion(1, -2, 1, &x1, &x2);
    print_solutions(result_code, x1, x2);

    printf("\na = -5, b = -1250, c = 0\nCorrect: x1=-250 x2=0\n");
    result_code = solve_square_equasion(-5, -1250, 0, &x1, &x2);
    print_solutions(result_code, x1, x2);

    printf("\na = 42, b = 0, c = 0\nCorrect: x=0\n");
    result_code = solve_square_equasion(42, 0, 0, &x1, &x2);
    print_solutions(result_code, x1, x2);
    
    printf("\na = -96, b = 0, c = 0\nCorrect: x=0\n");
    result_code = solve_square_equasion(42, 0, 0, &x1, &x2);
    print_solutions(result_code, x1, x2);

    printf("\na = 42, b = 69, c = 23\nCorrect: x1~-1.178, x2~-0.46488\n");
    result_code = solve_square_equasion(42, 69, 23, &x1, &x2);
    print_solutions(result_code, x1, x2);
}

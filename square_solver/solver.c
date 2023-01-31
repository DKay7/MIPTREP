#include <stdio.h>
#include <math.h>
#include <assert.h>
#include "square_solver.h"

//flexxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

int solve_square_equasion (double a, double b, double c, double* x1, double* x2)
{   
    assert (isfinite (a));
    assert (isfinite (b));
    assert (isfinite (c));
    assert (x1);
    assert (x2);
    assert (x1 != x2);

    if (is_double_zero (a))
    {
        return solve_linear_equasion (b, c, x1);
    }

    if (is_double_zero (b))
    {   
        double div = -c / a;
        if (div >= 0)
        {   
            if (is_double_zero (c))
            {
                *x1 = 0;
                return ONE_SOLUTION;
            }

            *x1 = sqrt (div);
            *x2 = -(*x1);

            return TWO_SOLUTIONS;
        }

        return NO_REAL_SOLUTIONS;
    }

    if (is_double_zero (c))
    {   
        solve_linear_equasion (a, b, x1);
        *x2 = 0;
        return TWO_SOLUTIONS; 
    }

    double D = b*b - 4*a*c;

    if (!isfinite (D))
    {
        return INFINITY_VALUE_ERROR;
    }

    if (is_double_zero (D))
    {   
        *x1 = -b / (2 * a);
        return ONE_SOLUTION;
    }

    if (D < 0)
    {   
        return NO_REAL_SOLUTIONS;
    }

    double sqrt_D = sqrt (D);
    double a2 = 2 * a;

    if (!(isfinite (sqrt_D) && isfinite (a2)))
    {
        return INFINITY_VALUE_ERROR;
    }

    *x1 = (-b + sqrt_D) / a2;
    *x2 = (-b - sqrt_D) / a2;

    return TWO_SOLUTIONS;
}

//flexxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

int solve_linear_equasion (double a, double b, double* x)
{   
    assert (isfinite(a));
    assert (isfinite(b));
    assert (x);

    if (is_double_zero (a))
    {
        if (is_double_zero (b))
        {   
            return INFINITY_NUMBER_OF_SOLUTIONS;
        }

        return NO_REAL_SOLUTIONS;
    }

    *x = -b / a;
    return ONE_SOLUTION;
}

//flexxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

void print_solutions (int result_code, double x1, double x2)
{   
    switch (result_code)
    {
        case INFINITY_NUMBER_OF_SOLUTIONS:
            printf ("There're infinity solutions\n\n");
            break;
        
        case NO_REAL_SOLUTIONS:
            printf ("There're no real solutions\n\n");
            break;
        
        case ONE_SOLUTION:
            printf ("There's only one solution: x=%lf\n\n", x1);
            break;
        
        case TWO_SOLUTIONS:
            printf ("Solutions: x1=%lf x2=%lf\n\n", x1, x2);
            break;
        
        case INFINITY_VALUE_ERROR:
            print_error ("print_solution", "Infinity value error code");
            break;

        default:
            print_error ("print_solutions", "Incorrect result code");
            break;
    }
}

//flexxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

int is_double_zero(double var)
{   
    static double epsilon = 1e-4;
    return fabs (var) < epsilon;
}

//flexxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

void print_error_func (const char* file, const int line, const char* current_function, 
                       const char* failed_function, const char* error_text)
{   
    assert (file);
    assert (line);
    assert (current_function);
    assert (failed_function);
    assert (error_text);

    fprintf (stderr, "File: %s\n"
                     "Line: %d\n"
                     "Current function: %s()\n"
                     "Failed function: %s()\n"
                     "Error message: %s\n",
                    file, line, current_function, failed_function, error_text);
}


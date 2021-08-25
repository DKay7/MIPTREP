#include "square_solver.h"

int solve_linear_equasion(double a, double b, double* x)
{   assert(isfinite(a));
    assert(isfinite(b));
    
    if (fabs(a) < EPSILON)
    {
        if (fabs(b) < EPSILON)
        {   
            return INFINITY_NUMBER_OF_SOLUTIONS;
        }

        return NO_REAL_SOLUTIONS;
    }

    *x = -b / a;
    return ONE_SOLUTION;
}

//flexxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

int solve_square_equasion(double a, double b, double c, double* x1, double* x2)
{   
    assert(isfinite(a));
    assert(isfinite(b));
    assert(isfinite(c));

    if (fabs(a) < EPSILON)
    {
        return solve_linear_equasion(b, c, x1);
    }

    if (fabs(b) < EPSILON)
    {   
        double div = -c / a;
        if (div >= 0)
        {   
            if (fabs(c) < EPSILON)
            {
                *x1 = 0;
                return ONE_SOLUTION;
            }
            
            *x1 = sqrt(div);
            *x2 = -(*x1);

            return TWO_SOLUTIONS;
        }

        return NO_REAL_SOLUTIONS;
    }

    if (fabs(c) < EPSILON)
    {   

        solve_linear_equasion(a, b, x1);
        *x2 = 0;
        return TWO_SOLUTIONS; 
    }

    double D = b*b - 4*a*c;

    if (fabs(D) < EPSILON)
    {   
        *x1 = *x2 = -b / (2 * a);
        return ONE_SOLUTION;
    }

    if (D < 0)
    {   
        return NO_REAL_SOLUTIONS;
    }

    double sqrt_D = sqrt (D);
    double a2 = 2 * a;

    *x1 = (-b + sqrt_D) / a2;
    *x2 = (-b - sqrt_D) / a2;

    return TWO_SOLUTIONS;
}

//flexxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

void print_solutions(int result_code, double x1, double x2)
{   
    assert(isfinite(x1) || isfinite(x2));

    switch (result_code)
    {
        case INFINITY_NUMBER_OF_SOLUTIONS:
            printf("There're infinity number of solutions\n\n");
            break;
        
        case NO_REAL_SOLUTIONS:
            printf("There're no real solutions\n\n");
            break;
        
        case ONE_SOLUTION:
            printf("There's only one solution: x=%lf\n\n", x1);
            break;
        
        case TWO_SOLUTIONS:
            printf("Solutions: x1=%lf x2=%lf\n\n", x1, x2);
            break;
        
        default:
            fprintf(stderr, "File: %s\nLine: %d\nCurrent function: %s() \
                \nFailed function: %s() \nError message: %s", \
                __FILE__, __LINE__, __func__, "solve_square_equasion", "Incorrect result code");
            break;
    }
}

//flexxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

int check_result(int result_code, double x1, double x2, double correct_x1, double correct_x2)
{
    switch (result_code)
    {
        case INFINITY_NUMBER_OF_SOLUTIONS:
            return isnan(x1) && isnan(x2);

        case NO_REAL_SOLUTIONS:
            return isnan(x1) && isnan(x2);
        
        case ONE_SOLUTION:
            return isnan(x2) && (fabs(x1 - correct_x2) < EPSILON || fabs(x1 - correct_x1) < EPSILON);
            
        case TWO_SOLUTIONS:
            return (fabs(x1 - correct_x1) < EPSILON && fabs(x2 - correct_x2) < EPSILON) || \
                    (fabs(x2 - correct_x1) < EPSILON && fabs(x1 - correct_x2) < EPSILON);
        
        default:
            fprintf(stderr, "File: %s\nLine: %d\nCurrent function: %s() \
                \nFailed function: %s() \nError message: %s", \
                __FILE__, __LINE__, __func__, "solve_square_equasion", "Incorrect result code");
            return 0;
    }
}

//flexxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

void unit_test(char* path)
{   
    int result_code = 0, num_of_tests = 0, k = 0, i = 0;
    double a = NAN, b = NAN, c = NAN;
    double correct_x1 = NAN, correct_x2 = NAN, x1 = NAN, x2 = NAN;
    
    FILE* unit_test_file = fopen(path, "r");
    assert (unit_test_file);

    fscanf (unit_test_file, "%d", &num_of_tests);

    for (i = 0; i < num_of_tests; i++)
    {   
        printf("\n-------------------------------\n");
        printf("Test number: %d\n", i);

        k = fscanf(unit_test_file, "%lg %lg %lg %lg %lg", &a, &b, &c, &correct_x1, &correct_x2);

        if (k != 5)
        {
            fprintf(stderr, "File: %s\nLine: %d\nCurrent function: %s()\
                    \nFailed function: %s()\nError message: %s", \
                    __FILE__, __LINE__, __func__, "unit_test", "Incorrect input!\n");
            
            continue;
        }
        
        printf("a=%lf, b=%lf, c=%lf\ncorrect: x1=%lf, x2=%lf\n", \
                a, b, c, correct_x1, correct_x2);
        
        result_code = solve_square_equasion(a, b, c, &x1, &x2);
        
        if (check_result(result_code, x1, x2, correct_x1, correct_x2))
        {
            printf("\n\033[92mTEST PASSED\033[0m\n");
        }

        else
        {   
            printf("\n\033[91mTEST FAILED. Actual solutions:\033[0m\n");
            print_solutions(result_code, x1, x2);
        }
        
        x1 = NAN;
        x2 = NAN;
    }

    fclose(unit_test_file);
}

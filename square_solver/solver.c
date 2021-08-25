#include "square_solver.h"

int solve_linear_equasion (double a, double b, double* x)
{   assert (isfinite(a));
    assert (isfinite(b));
    assert (x);

    if (fabs (a) < EPSILON)
    {
        if (fabs (b) < EPSILON)
        {   
            return INFINITY_NUMBER_OF_SOLUTIONS;
        }

        return NO_REAL_SOLUTIONS;
    }

    *x = -b / a;
    return ONE_SOLUTION;
}

//flexxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

int solve_square_equasion (double a, double b, double c, double* x1, double* x2)
{   
    assert (isfinite (a));
    assert (isfinite (b));
    assert (isfinite (c));
    assert (x1);
    assert (x2);
    assert (x1 != x2);

    if (fabs (a) < EPSILON)
    {
        return solve_linear_equasion (b, c, x1);
    }

    if (fabs (b) < EPSILON)
    {   
        double div = -c / a;
        if (div >= -EPSILON)
        {   
            if (fabs (c) < EPSILON)
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

    if (fabs (c) < EPSILON)
    {   
        solve_linear_equasion (a, b, x1);
        *x2 = 0;
        return TWO_SOLUTIONS; 
    }

    double D = b*b - 4*a*c;

    if (fabs (D) < EPSILON)
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

    *x1 = (-b + sqrt_D) / a2;
    *x2 = (-b - sqrt_D) / a2;

    return TWO_SOLUTIONS;
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
        
        default:
            fprintf (stderr, "File: %s\nLine: %d\nCurrent function: %s() \
                    \nFailed function: %s() \nError message: %s", \
                    __FILE__, __LINE__, __func__, "solve_square_equasion", 
                    "Incorrect result code");
            break;
    }
}

//flexxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

int check_result (int result_code, double x1, double x2,  
                  int correct_result_code,  double correct_x1, double correct_x2)
{   
    if (correct_result_code != result_code)
    {
        return 0;
    }

    switch (result_code)
    {
        case INFINITY_NUMBER_OF_SOLUTIONS:
            return isnan (x1) && isnan (x2);

        case NO_REAL_SOLUTIONS:
            return isnan (x1) && isnan (x2);
        
        case ONE_SOLUTION:
            return isnan (x2) && (fabs (x1 - correct_x2) < EPSILON || fabs (x1 - correct_x1) < EPSILON);
            
        case TWO_SOLUTIONS:
            return (fabs (x1 - correct_x1) < EPSILON && fabs (x2 - correct_x2) < EPSILON) || \
                   (fabs (x2 - correct_x1) < EPSILON && fabs (x1 - correct_x2) < EPSILON);
        
        default:
            fprintf (stderr, "File: %s\nLine: %d\nCurrent function: %s() \
                    \nFailed function: %s() \nError message: %s",
                    __FILE__, __LINE__, __func__, "solve_square_equasion", 
                    "Incorrect result code");
            return 0;
    }
}

//flexxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

int process_test (FILE* unit_test_file, int* solver_result_code, double* x1, double* x2)
{   
    assert (unit_test_file);
    assert (solver_result_code);
    assert (x1);
    assert (x2);
    assert (x1 != x2);

    int correct_solver_result_code = SOLVER_DEFAULT;
    double a = NAN, b = NAN, c = NAN;
    double correct_x1 = NAN, correct_x2 = NAN;

    int scanf_check = fscanf (unit_test_file, "%lg %lg %lg %d %lg %lg", &a, &b, &c, 
                             &correct_solver_result_code, &correct_x1, &correct_x2);
 
    if (scanf_check != 6)
    {
        fprintf (stderr, "File: %s\nLine: %d\nCurrent function: %s()\
                \nFailed function: %s()\nError message: %s", \
                __FILE__, __LINE__, __func__, "unit_test", "Incorrect input!\n");
        
        return INPUT_ERROR;
    }
    
    printf ("a=%lf, b=%lf, c=%lf\ncorrect: x1=%lf, x2=%lf\n",
           a, b, c, correct_x1, correct_x2);
    
    *solver_result_code = solve_square_equasion (a, b, c, x1, x2);
    
    if (check_result (*solver_result_code, *x1, *x2, correct_solver_result_code, correct_x1, correct_x2))
    {
       return TEST_PASSED;
    }

    return TEST_FAILED;
}

//flexxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

void unit_test (const char* path)
{   
    assert (path);

    int i = 0, num_of_tests = 0, test_result_code = TEST_DEFAULT, solver_result_code = SOLVER_DEFAULT;
    double solved_x1 = NAN, solved_x2 = NAN;
    FILE* unit_test_file = fopen (path, "r");

    if (!unit_test_file)
    {
        fprintf (stderr, "File: %s\nLine: %d\nCurrent function: %s()\
                \nFailed function: %s()\nError message: %s",
                __FILE__, __LINE__, __func__, "unit_test", "Can't open file with tests\n");
        return;
    }

    fscanf (unit_test_file, "%d", &num_of_tests);

    for (i = 0; i < num_of_tests; i++)
    {   
        printf ("\n-------------------------------\n");
        printf ("Test number: %d\n", i);

        test_result_code = process_test (unit_test_file, &solver_result_code,  &solved_x1, &solved_x2);

        switch (test_result_code)
        {
            case INPUT_ERROR:
                continue; 
                break;

            case TEST_FAILED:
                printf ("\n\033[91mTEST FAILED. Actual solutions:\033[0m\n");
                print_solutions (solver_result_code, solved_x1, solved_x2);
                break;

            case TEST_PASSED:
                printf ("\n\033[92mTEST PASSED\033[0m\n");
                break;

            default:
                fprintf (stderr, "File: %s\nLine: %d\nCurrent function: %s() \
                        \nFailed function: %s() \nError message: %s", \
                        __FILE__, __LINE__, __func__, "process_test", 
                        "Incorrect result code");
                continue;
                break;
        }

        solved_x1 = NAN;
        solved_x2 = NAN;
    }

    fclose (unit_test_file);
}

#include <stdio.h>
#include <assert.h>
#include <math.h>
#include "unit_test.h"
#include "square_solver.h"

//flexxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

void unit_test (const char* path)
{   
    assert (path);
    
    int i = 0, num_of_tests = 0, test_result_code = TEST_DEFAULT, solver_result_code = SOLVER_DEFAULT;
    double solved_x1 = NAN, solved_x2 = NAN;
    FILE* unit_test_file = fopen (path, "r");

    if (!unit_test_file)
    {   
        print_error ("unit_test", "Error with file pointer");
        return;
    }

    if (ferror (unit_test_file))
    {
        print_error ("unit_test", "Error with file descriptor");
        return;
    }

    fscanf (unit_test_file, "%d", &num_of_tests);

    for (i = 0; i < num_of_tests; i++)
    {   
        printf ("\n-------------------------------\n"
                "Test number: %d\n", i);

        test_result_code = process_test (unit_test_file, &solver_result_code,  &solved_x1, &solved_x2);

        switch (test_result_code)
        {
            case INPUT_ERROR:
                continue; 
                break;

            case TEST_FAILED:
                printf ("\n" RED_COLOR(TEST FAILED. Actual solutions:) "\n");
                print_solutions (solver_result_code, solved_x1, solved_x2);
                break;

            case TEST_PASSED:
                printf ("\n" GREEN_COLOR(TEST PASSED) "\n");
                break;

            default:
                print_error ("unit_test", "Incorrect result code");
                continue;
                break;
        }

        solved_x1 = NAN;
        solved_x2 = NAN;
    }

    fclose (unit_test_file);
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
        print_error ("process_test", "Incorrect input!");    
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
            return isnan (x2) && (is_double_zero (x1 - correct_x2) || is_double_zero (x1 - correct_x1));
            
        case TWO_SOLUTIONS:
            return (is_double_zero (x1 - correct_x1) && is_double_zero (x2 - correct_x2)) ||
                   (is_double_zero (x2 - correct_x1) && is_double_zero (x1 - correct_x2));
        
        case INFINITY_VALUE_ERROR:
            print_error ("check_result", "Infinity value error code");
            return 0;

        default:
            print_error ("check_result", "Incorrect result code");
            return 0;
    }
}


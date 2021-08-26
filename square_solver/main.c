#include "square_solver.h"
#include "unit_test.h"
#include <math.h>

int main(int argc, char* argv[])
{   
    #ifdef _DEBUG
        const char* path = "tests/unit_test_file.txt";

        if (argc == 2)
        {
            path = argv[1];
        }

        unit_test (path);

        return 0;
    
    #else
        double a = NAN, b = NAN, c = NAN, x1 = NAN, x2 = NAN;
        int result_code = 0;

        printf ("Enter coefficients: a, b, c\n");
        int scanf_check = scanf ("%lf %lf %lf", &a, &b, &c);

        if (scanf_check != 3)
        {   
            print_error ("main", "Incorrect number of arguments");
            return -1;
        }

        if (!(isfinite (a) && isfinite (b) && isfinite (c)))
        {
            print_error ("main", "Coefficients are incorrect");
            return -1;
        }

        result_code = solve_square_equasion (a, b, c, &x1, &x2);
        print_solutions (result_code, x1, x2);

        return 0;

    #endif
}
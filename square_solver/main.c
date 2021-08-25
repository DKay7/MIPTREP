#include "square_solver.h"

int main(int argc, char* argv[])
{   
    #ifdef _DEBUG
        const char* path = "unit_test_file.txt";

        if (argc == 2)
        {
            path = argv[1];
        }

        unit_test (path);
    
    #else
        double a = NAN, b = NAN, c = NAN, x1 = NAN, x2 = NAN;
        int result_code = 0;

        printf ("Enter coefficients: a, b, c\n");
        int scanf_check = scanf ("%lf\n%lf\n%lf", &a, &b, &c);

        if (scanf_check != 3)
        {
            fprintf (stderr, "File: %s\nLine: %d\nCurrent function: %s()\
                    \nFailed function: %s()\nError message: %s",
                    __FILE__, __LINE__, __func__, "main", "Incorrect number of arguments\n");
            return -1;
        }

        result_code = solve_square_equasion (a, b, c, &x1, &x2);
        print_solutions (result_code, x1, x2);
    #endif

}
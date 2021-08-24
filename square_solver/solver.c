#include "square_solver.h"


int solve_square_equasion(double a, double b, double c)
{   
    assert(a and b and c);
    
    if (abs(a) < epsilon)
    {
        fprintf(stderr, "File: %s\nLine: %d\nCurrent function: %s()\nFailed function: %s()\nError message: %s", \
                __FILE__, __LINE__, __func__, "solve_square_equasion", "x^2 coefficient should not be zero\n");
        return -1;
    }

    double D = b*b - 4*a*c;

    if (D < 0)
    {   
        printf("There're no any real solutions\n");
        return 0;
    }

    double x1 = (-b + sqrt (D)) / (2 * a);
    double x2 = (-b - sqrt (D)) / (2 * a);

    if (abs(D) < epsilon)
    {
        printf("The only solution is %lf\n", x1);
        return 0;
    }

    printf("The solutions are %lf, %lf\n", x1, x2);
    return 0;

}

//flexxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

void unit_test()
{   
    printf("\na = 0, b = 1, c = 2\nCorrect: Error\n");
    solve_square_equasion(0, 1, 2);

    printf("\na = 1, b = 2, c = 1\nCorrect: x=-1\n");
    solve_square_equasion(1, 2, 1);

    printf("\na = 1, b = -2, c = 1\nCorrect: x=1\n");
    solve_square_equasion(1, -2, 1);

    printf("\na = -5, b = -1250, c = 0\nCorrect: x1=-250 x2=0\n");
    solve_square_equasion(-5, -1250, 0);
    
    printf("\na = 42, b = 0, c = 0\nCorrect: x=0\n");
    solve_square_equasion(42, 0, 0);

    printf("\na = -96, b = 0, c = 0\nCorrect: x=0\n");
    solve_square_equasion(42, 0, 0);

    printf("\na = 42, b = 69, c = 23\nCorrect: x1~-1.178, x2~-0.46488\n");
    solve_square_equasion(42, 69, 23);
}

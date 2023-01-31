#include <math.h>
#include <stdio.h>

//flexxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

double angle(double x1, double y1, double x2, double y2)
{ 
    return acos( (x1*x2 + y1*y2) / ( sqrt(x1*x1 + y1*y1) * sqrt(x2*x2 + y2*y2) ) );
}

//flexxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

int main ()
{   
    double x1 = 0, y1 = 0, x2 = 0, y2 = 0;
    scanf ("%lg %lg %lg %lg", &x1, &y1, &x2, &y2);

    printf ("%.14lf\n", angle (x1, y1, x2, y2));
}
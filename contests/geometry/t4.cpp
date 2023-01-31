#include <math.h>
#include <stdio.h>

//flexxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

double distance(double x0, double y0, double x1, double y1, double x2, double  y2) {
   return fabs((y2-y1)*x0-(x2-x1)*y0+x2*y1-y2*x1) / sqrt(pow(y2-y1, 2.0) + pow(x2-x1, 2.0));
}

//flexxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

int main ()
{   
    double x_point, y_point, x1_line, y1_line, x2_line, y2_line;

    scanf ("%lg %lg %lg %lg %lg %lg", &x_point, &y_point, &x1_line, &y1_line, &x2_line, &y2_line);
    
    double dist = distance (x_point, y_point, x1_line, y1_line, x2_line, y2_line);

    printf ("%.10f\n", dist);
    return 0;
}
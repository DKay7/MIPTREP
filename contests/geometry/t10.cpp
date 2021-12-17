#include <stdio.h>

int main()
{   
    double x1, y1, x2, y2, x3, y3;
    scanf ("%lg %lg %lg %lg %lg %lg", &x1, &y1, &x2, &y2, &x3, &y3);
    
    double m_x = (x1 + x2 + x3) / 3, m_y = (y1 + y2 + y3) / 3;
    printf ("%.10f %.10f\n", m_x, m_y);

    return 0;
}
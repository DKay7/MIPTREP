#include <stdio.h>

//-----------------------------------------------------

typedef struct
{
    double x;
    double y;
} Dot;
//-----------------------------------------------------

int DotCtor (Dot* dot, double x, double y);

//-----------------------------------------------------

int FindIfDotInArea (Dot* dot);

//-----------------------------------------------------

int main ()
{   
    Dot dot;
    double x = 0, y = 0;
    scanf ("%lg %lg", &x, &y);
    DotCtor (&dot, x, y);
    
    int in_area = FindIfDotInArea (&dot);
    
    if (in_area)
    {
        printf ("YES\n");
    }
    else
    {
        printf ("NO\n");
    }

    return 0;
}

//-----------------------------------------------------

int DotCtor (Dot* dot, double x, double y)
{
    dot->x = x;
    dot->y = y;

    return 0;
}

int FindIfDotInArea (Dot* dot)
{   
    int less_than_parabola = (dot->y < -3 + dot->x*dot->x);
    int less_than_2_area = less_than_parabola && dot->y < 2;
    int more_than_2_area = !less_than_parabola && dot->y >= 2;

    if (less_than_2_area || more_than_2_area)
    {
        return 1;
    }
    
    return 0;
}
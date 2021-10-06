#include <stdlib.h>
#include <stdio.h>

//flexxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

struct Point {
        int x;
        int y;
};

//flexxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

typedef struct Point Point;

//flexxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

int cmp_Point(const void * p1, const void * p2)
{
    Point point1 = *(const Point*) p1;
    Point point2 = *(const Point*) p2;

    int r1 = point1.x * point1.x + point1.y * point1.y;
    int r2 = point2.x * point2.x + point2.y * point2.y; 

    if (r1 == r2)
    {
        if (point1.x == point2.x)
        {
            return point1.y - point2.y;
        }

        return point1.x - point2.x;
    }
    
    return r1 - r2;
}

//flexxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

int main ()
{
    Point array[1000];
    int num = 0;

    scanf ("%d", &num);
    for (int i = 0; i < num; i++)
    {
        scanf("%d %d", &array[i].x, &array[i].y);
    }

    qsort (array, num, sizeof(Point), cmp_Point);
    
    for (int i = 0; i < num; i++)
    {
        printf("%d %d\n", array[i].x, array[i].y);
    }

    printf("\n");
    return 0;
}
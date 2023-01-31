#include <stdio.h>
#include <malloc.h>

#define lld double
#define ll  long long unsigned
 
struct Point {
    int x;
    int y;
};

struct Rect {
    struct Point lt; // left top
    struct Point rb; // right bottom
};

struct Rect * transform (const struct Rect * src)
{   
    struct Rect* transformed = (struct Rect*) calloc (1, sizeof (*transformed));

    struct Point common = {src->rb.x, src->lt.y};

    (*transformed) = {
        common,
        {
          common.x + (common.y - src->rb.y),
          common.y - (common.x - src->lt.x)
        }
    };

    return transformed;
}

int main()
{   
    struct Rect a = {{-1, 1}, {4, -2}};
    struct Rect * rect;
    rect = transform(&a);
    printf("%d %d %d %d\n", a.lt.x, a.lt.y, a.rb.x, a.rb.y);
    printf("%d %d %d %d\n", rect->lt.x, rect->lt.y, rect->rb.x, rect->rb.y);
    free(rect);
    return 0;
}

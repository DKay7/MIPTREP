#include <stdio.h>

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

struct Rect transform (struct Rect r)
{  
    struct Point common = { r.lt.x, r.rb.y };

    struct Rect transformed = {
      {
          common.x - (r.lt.y - common.y),
          common.y + (r.rb.x - common.x)
      },
      common
    };

    return transformed;
}

int main()
{
    struct Rect rect, a = {{-1, 1}, {4, -2}};
    rect = transform(a);
    printf("%d %d %d %d\n", a.lt.x, a.lt.y, a.rb.x, a.rb.y);
    printf("%d %d %d %d\n", rect.lt.x, rect.lt.y, rect.rb.x, rect.rb.y);
    return 0;
}

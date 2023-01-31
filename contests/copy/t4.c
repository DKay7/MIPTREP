#include <assert.h>
#include <stdlib.h>

//flexxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx
void swap(void *a, void *b, size_t el_size)
{
    assert(a);
    assert(b);

    char *a_arr = (char *) a;
    char *b_arr = (char *) b;
    char tmp = 0;

    for (unsigned i = 0; i < el_size; i++) {
        tmp = a_arr[i];
        a_arr[i] = b_arr[i];
        b_arr[i] = tmp;
    }
}

void reverse(void *arr, int size, int n)
{
    char *_arr = (char *) arr;


    for (int i = 0; i < (n / 2); i++) {
        swap(&_arr[i * size], &_arr[(n - i - 1) * size], size);
    }

    return;
}

struct Test {
    int x;
    double y;
};
enum { ARRLEN = 4 };

void test()
{
    int i;
    struct Test arr[ARRLEN] =
        { { 1, 1.0 }, { 2, 2.0 }, { 3, 3.0 }, { 4, 4.0 } };
    struct Test answ[ARRLEN] =
        { { 4, 4.0 }, { 3, 3.0 }, { 2, 2.0 }, { 1, 1.0 } };
    reverse(arr, sizeof(struct Test), ARRLEN);
    for (i = 0; i < ARRLEN; ++i) {
        if (arr[i].x != answ[i].x)
            abort();
        if (arr[i].y != answ[i].y)
            abort();
    }
}

int main()
{
    test();
}

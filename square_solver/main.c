#include "square_solver.h"

int main(int argc, char* argv[])
{
    if (argc != 2)
    {
        fprintf(stderr, "File: %s\nLine: %d\nCurrent function: %s() \
                 \nFailed function: %s() \nError message: %s", \
                 __FILE__, __LINE__, __func__, "main", "Incorrect input!\n");

        return -1;
    }

    unit_test(argv[1]);
}
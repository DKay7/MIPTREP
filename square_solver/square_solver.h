#include <stdio.h>
#include <math.h>
#include <assert.h>

# define epsilon 1e-7

//flexxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

enum return_codes
{
    INFINITY_NUMBER_OF_SOLUTIONS = -0x00000001,
    NO_REAL_SOLUTIONS = 0x00000000,
    ONE_SOLUTION = 0x00000001,
    TWO_SOLUTIONS = 0x00000002
};

// Function to find square equasion solutions
int solve_square_equasion(double, double, double, double*, double*);

// Function to print solution
void print_solutions(int, double, double);

// Function to proceed tests
void unit_test();

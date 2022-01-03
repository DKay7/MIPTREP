#include "calculate.h"
#include <stdio.h>
#include <assert.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

//flexxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

const char* s = NULL;

int main ()
{
    char* str = NULL;
    scanf ("%m[^\n]s", &str);
    double result = GetG (str);
    printf ("%lg\n", result);
    free (str);
    return 0;
}

//flexxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

double GetG (const char* str)
{
    s = str;
    double val = GetE ();
    REQUIRED (TERMINATOR_CHAR, "No terminator char");

    return val;
}

//flexxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

double GetE ()
{   
    SkipTabs ();
    double val = 0;

    val = GetT();

    if (*s == '+')
    {   
        s++;
        val += GetE();
    }
    
    else if (*s == '-')
    {   
        s++;
        val -= GetE();
    }

    SkipTabs ();
    return val;
}

//flexxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

double GetT ()
{   
    SkipTabs ();
    double val = GetU();

    if (*s == '*')
    {   
        s++;
        val *= GetT ();
    }
    else if (*s == '/')
    {   
        s++;
        val /= GetT ();
    }

    SkipTabs ();
    return val;
}

//flexxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx
double GetU ()
{   
    SkipTabs ();

    if (strstr (s, "sin") == s)
    {   
        s += 3;
        double val = sin (GetE());
        SkipTabs ();

        return val;
    }
    
    else if (strstr (s, "cos") == s)
    {
        s += 3;
        double val = cos (GetE());
        SkipTabs ();
        
        return val;
    }

    else if (strstr (s, "ln") == s)
    {
        s += 2;
        double val = log (GetE());
        SkipTabs ();
        
        return val;
    }

    else
    {
        double val = GetP();
        SkipTabs ();

        return val;
    }
}

double GetP ()
{   
    SkipTabs ();
    
    if (*s == '(')
    {   
        s++;
        double val = GetE();
        REQUIRED(')', "No close brackets");
        return val;
        SkipTabs ();
    }

    else
    {   
        double val = GetN();
        SkipTabs ();

        return val;
    }
}

//flexxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx
double GetD ()
{   
    printf ("CUR S %c\n", *s);
    double val = *s - '0';
    s++;

    return val; 
}

// double GetN ()
// {
//     const char* old_s = s;
//     double val = GetD ();
    
//     if ('0' <= *s && *s <= '9')
//     {   
//         printf ("CUR VAL %d", val);
//         val = 10 * GetN () + val;
//     }

//     if (s == old_s)
//     {
//         SyntaxError("Number required");
//     }
    
//     return val;
//}

double GetN ()
{
    double val = 0;
    const char* old_s = s;

    while ('0' <= *s && *s <= '9')
    {
        val = 10 * val + (*s - '0');
        s++;
    }

    if (*s == '.')
    {   
        s ++;

        const char* old_s_fractional = s;
        double power = 1;

        while ('0' <= *s && *s <= '9')
        {
            val = 10 * val + (*s - '0');
            power *= 10;

            s++;
        }

        val /= power;
        if (old_s_fractional == s)
        {
            SyntaxError("Number required");
        }

    }

    if (old_s == s)
    {
        SyntaxError("Number required");
    }

    return val;
}

void SkipTabs ()
{
    while (*s == ' ')
    {
        s++;
    }
}

void SyntaxError(const char* str)
{
    fprintf (stderr, "SYNTAX ERROR: %s\n", str);
    return;
}
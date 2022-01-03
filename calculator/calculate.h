

//flexxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

#define TERMINATOR_CHAR '\0'

#define REQUIRED(SYMBOL, ERR)   \
    if (*s == SYMBOL)           \
    {                           \
        s++;                    \
    }                           \
    else SyntaxError (ERR);

//flexxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

double GetG (const char* str);
double GetE ();
double GetT ();
double GetP ();
double GetN ();
double GetU ();
void SkipTabs ();
void SyntaxError(const char* str);
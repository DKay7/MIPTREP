t

//flexxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

struct namednum {
  char *name;
  int number;
};

//flexxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

enum { ARRLEN = 4 };

//flexxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

char *alstr(const char *orig) {
    int len;
    char *ret;
    assert(orig);
    len = strlen(orig);
    ret = (char*) calloc(len + 1, sizeof(char));
    strcpy(ret, orig);
    return ret;
}

//flexxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

t
//flexxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

void test() {
    int i;
    struct namednum arr[ARRLEN] = { 
      {alstr("abc"), 1}, {alstr("def"), 2}, 
      {alstr("ghi"), 3}, {alstr("klm"), 4} 
    };
    struct namednum answ[ARRLEN];
    
    // вызов namednumcpy
    namednumcpy(answ, arr, ARRLEN);
    
    for (i = 0; i < ARRLEN; ++i)
      arr[i].name[0] = '\0';

    assert(0 == strcmp(answ[0].name, "abc"));
    assert(0 == strcmp(answ[1].name, "def"));
    assert(0 == strcmp(answ[2].name, "ghi"));
    assert(0 == strcmp(answ[3].name, "klm"));

    for (i = 0; i < ARRLEN; ++i) {
      free(arr[i].name);
      free(answ[i].name);
    }
}

int main()
{
    test();
}
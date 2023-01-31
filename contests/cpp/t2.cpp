/*
Эту часть сдавать НЕ надо. Она будет вставлена ПЕРЕД Вашим кодом.
*/

#include <iostream>
#include <cstdlib>
#include <math.h>
using namespace std;

class Time {
  public:
    int hour;
    int min;
};

/*
А вот здесь начинается Ваша функция, которую Вы сдаёте:
*/
enum IS_EQUAL
{   
    NOT_EQUAL = 0,
    EQUAL = 1,
};

int isEqual(Time a, int min)
{
    int full_mins = a.hour * 60 + a.min;

    if (full_mins == min)
    {
        return EQUAL;
    }

    return NOT_EQUAL;
}


/*
Здесь Ваша функция кончается. Для удобства отладки приведено то, что будет вставлено ПОСЛЕ  Вашего кода.
*/



int main()
{
    Time a, newtime;
    int min;
    int res;

    // Получить a  из консоли 


    cin >> a.hour >> a.min;
    // Получить min  из консоли 

    cin >> min;
    res = isEqual(a, min);
    cout << res << endl;
}

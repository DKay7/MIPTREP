/*!
\file
\brief Заголовочный файл с прототипами функций

Данный файл содержит в себе прототипы всех функций,
используемых данной программой
*/


#include <stdio.h>
#include <math.h>
#include <assert.h>

/// Используется для сравнения ```double```
#define EPSILON 1e-4


//flexxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx


/// Набор возвращаемых кодов, в зависимости от количества решений
enum return_codes
{
    INFINITY_NUMBER_OF_SOLUTIONS = -1, ///< Бескончно много решений (x - любое)
    NO_REAL_SOLUTIONS = 0, ///< Нет действительных решений
    ONE_SOLUTION = 1,  ///< Одно действительное решение
    TWO_SOLUTIONS = 2 ///< Два действительных решения
};

//flexxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

/*!
\brief Решает линейное уравнение вида ax + b = 0
Данная функция необходима, поскольку в некоторых случаях 
квадратное уравнение вырождается в линейное

\param a,b Соответствующие коэффициенты
\param x Указатель на переменную, куда будет записано решение
\return Один из кодов \link return_codes \endlink
*/
int solve_linear_equasion(double a, double b, double* x);

//flexxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

/*!
\brief Решает квадратное уравнение вида ax^2 + bx + c = 0

\param a,b,c Соответствующие коэффициенты
\param x1, x2 Указатели на переменнык, куда будут записаны решения
\return Один из кодов \link return_codes \endlink
*/
int solve_square_equasion(double a, double b, double c, double* x1, double* x2);

//flexxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

/*!
\brief Распечатывает решение уравнения
Данная процедура печатает в stdout решения квадратного уравнения, полученные 
функцией \link solve_square_equasion \endlink

\param result_code Один из кодов \link return_codes \endlink, возвращенный 
функцией \link solve_square_equasion \endlink
\param x1, x2 Решения уравнения, полученные функцией \link solve_square_equasion \endlink
*/
void print_solutions(int result_code, double x1, double x2);

/*!
\brief Сверяет корни уравнения с эталонами
Данная функция необходима для проверки на правильность полученных корней уравнения
Она используется в функции \link unit_test \endlink после выполнения теста

\param result_code Один из кодов \link return_codes \endlink, возвращенный 
функцией \link solve_square_equasion \endlink
\param x1, x2 Решения уравнения, полученные функцией \link solve_square_equasion \endlink
\param correct_x1,correct_x2 Правильные решения для сверки
*/
int check_result(int result_code, double x1, double x2, double correct_x1, double correct_x2);


/*!
\brief Функция для проведения юнит-тестов

\param path Путь к файлу с тестами
*/
void unit_test(char* path);

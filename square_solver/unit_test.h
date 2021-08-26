/*!
\file
\brief Заголовочный файл с прототипами функций для проведения тестов

\details Данный файл содержит в себе прототипы всех функций,
используемых при проведении тестов функций решения квадратного уравнения
*/

#include "stdio.h"

/// Макрос для окраски текста в зеленый цвет
#define GREEN_COLOR(text) "\033[92m"#text"\033[0m"

/// Макрос для окраски текста в красный цвет
#define RED_COLOR(text) "\033[91m"#text"\033[0m"

//flexxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

/*!
\brief Сверяет корни уравнения с эталонами
Данная функция необходима для проверки на правильность полученных корней уравнения
Она используется в функции \link unit_test \endlink после выполнения теста

\param[in] result_code Один из кодов \link solver_return_codes \endlink, возвращенный 
функцией \link solve_square_equasion \endlink

\param[in] x1, x2 Решения уравнения, полученные функцией \link solve_square_equasion \endlink

\param[in] correct_x1, correct_x2, correct_result_code Правильные решения для сверки

\return 0 -- если решения не совпадают, 1 -- если совпадают 
*/
int check_result (int result_code, double x1, double x2,  
                  int correct_result_code,  double correct_x1, double correct_x2);

//flexxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

/*!
\brief Функция для проведения одного теста

\param[in] unit_test_file Указатель на файл, откуда будет прочитана строка

\param[out] solver_result_code Указатель на переменную, куда будет 
записан код \link solver_return_codes \endlink

\param[out] x1,x2 Указатели на переменные, куда будут записаны решения, 
полученные \link solve_square_equasion \endlink. 
В случае непрохождения теста, эти значения будут необходимы для отладки

\return Один из кодов \link test_return_codes \endlink
*/
int process_test (FILE* unit_test_file, int* solver_result_code, double* x1, double* x2);

//flexxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

/*!
\brief Функция для проведения юнит-тестов

Файл с тестами должен иметь следующуюю структуру:
1. В первой строке файла содержится число n -- количество тестов. 
   Далее идут n строк с тестами непосредственно.
2. Каждая строка имеет вид:
   коэффициент_а коэффициент_b коэффициент_c количество_корней верный_x1 верный_x2
   
   Коэффициенты a, b, c -- числа с плавающей точкой -- коэффициенты в уравнении вида ```ax^2 + bx + c```

   Количество корней -- целое число -- соответствующий код из \link solver_return_codes \endlink
   
   Верные ответы x1, x2  -- числа с плавающей точкой, в случае если один или оба корня отсутствуют
   либо уравнение имеет бесконечно много корней, нужно передать NAN в качестве значения верного ответа,
   соответственно, либо только для x1 или x2, либо сразу для обоих

\param[in] path Путь к файлу с тестами
*/
void unit_test (const char* path);

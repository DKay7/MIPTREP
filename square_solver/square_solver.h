/*!
\file
\brief Заголовочный файл с прототипами функций для решения квадратного уравнения

\details Данный файл содержит в себе прототипы функций, используемых
для решения квадратного уравнения и вывода результата
*/

/// Макрос для print_error_func, который автоматически подставляет
/// Файл и строку в сообщение об ошибке
#define print_error(failed_function, error_text) print_error_func(__FILE__, __LINE__, __FUNCTION__, failed_function, error_text)

/*! 
Перечисление кодов, которые функции \link solve_square_equasion \endlink 
и \link solve_linear_equasion \endlink возвращают в зависимости от количества решений
*/
enum solver_return_codes
{   
    INFINITY_VALUE_ERROR = -3, ///< Ошибка, при которой одна из переменных приняла значение INFINITY
    SOLVER_DEFAULT = -2, ///< Значение по умолчанию
    INFINITY_NUMBER_OF_SOLUTIONS = -1, ///< Бескончно много решений (x - любое)
    NO_REAL_SOLUTIONS = 0, ///< Нет действительных решений
    ONE_SOLUTION = 1,  ///< Одно действительное решение
    TWO_SOLUTIONS = 2 ///< Два действительных решения
};

//flexxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

/*!
\brief Проверяет, является ли число с плавающей точкой нулем

\param[in] var Число для порверки

\return 1, если число равно 0, иначе -- 0. 
*/
int is_double_zero(double var);

//flexxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

/*!
\brief Печатает ошибку в stderr

\param[in] file Файл, в котором произошла ошибка
\param[in] line Строка в которой произошла ошибка
\param[in] current_function Имя функции, из которой была вызвана \link print_error_func \endlink
\param[in] failed_function Имя функции, в которой возникла ошибка
\param[in] error_text Текст ошибки


\return 1, если число равно 0, иначе -- 0. 
*/
void print_error_func (char * const file, const int line, char * const current_function, 
                       char * const failed_function, char * const error_text);


//flexxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

/*!
\brief Решает линейное уравнение вида ax + b = 0
Данная функция необходима, поскольку в некоторых случаях 
квадратное уравнение вырождается в линейное

\param[in] a,b Соответствующие коэффициенты

\param[out] x Указатель на переменную, куда будет записано решение

\return Один из кодов \link solver_return_codes \endlink
*/
int solve_linear_equasion (double a, double b, double* x);

//flexxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

/*!
\brief Решает квадратное уравнение вида ax^2 + bx + c = 0

\param[in] a,b,c Соответствующие коэффициенты

\param[out] x1, x2 Указатели на переменнык, куда будут записаны решения

\return Один из кодов \link solver_return_codes \endlink
*/
int solve_square_equasion (double a, double b, double c, double* x1, double* x2);

//flexxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

/*!
\brief Распечатывает решение уравнения
Данная процедура печатает в stdout решения квадратного уравнения, полученные 
функцией \link solve_square_equasion \endlink

\param[in] result_code Один из кодов \link solver_return_codes \endlink, возвращенный 
функцией \link solve_square_equasion \endlink

\param[in] x1, x2 Решения уравнения, полученные функцией \link solve_square_equasion \endlink
*/
void print_solutions (int result_code, double x1, double x2);

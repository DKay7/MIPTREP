/**
*   @file
*   @brief Файл содержит в себе прототипы функций для работы со стаком и саму структуру стака.
*/

#include <stdio.h>

//flexxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

#define GREEN_COLOR(text) "\033[92m" #text "\033[0m"
#define RED_COLOR(text) "\033[91m" #text "\033[0m"

//flexxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

#define StackDump(stack) StackDumpFunc (stack, __LINE__, __PRETTY_FUNCTION__, __FILE__, #stack)

//flexxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

#define StackCtor(stack, size) StackCtorFunc (stack, size, #stack, __PRETTY_FUNCTION__, __LINE__, __FILE__)

//flexxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

/// Объявление типа стака. Необходимо, чтобы стак был независим от типа данных.
typedef int stack_type;
typedef unsigned long long hummingbird_type;
//flexxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

const hummingbird_type HUMMINGBIRD = (hummingbird_type) 0xDEAD0DED;

//flexxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

/** @struct Stack
 *  @brief Структура стека.
 */
typedef struct Stack
{   
    hummingbird_type start_bird;
    size_t size;                /**< Поле Stack#size хранит размер занятого пространства. */
    size_t capacity;            /**< Поле Stack#capacity хранит размер выделенной памяти. */
    stack_type* data;           /**< Поле Stack#data хранит указатель на начало массива с данными. */
    int error_code;             /**< Поле Stack#error_code хранит ошибку. */
    const char* filename;       /**< Поле Stack#filename хранит имя файла, в котором был проинициализирован стек. */
    int line;                   /**< Поле Stack#line хранит номер строки, в которой был проинициализирован стек. */
    const char* stack_name;     /**< Поле Stack#stack_name хранит имя объекта стека. */
    const char* init_func;
    void (*print_function)(stack_type*);
    unsigned long long hash;
    hummingbird_type end_bird;
} Stack;

//flexxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

/**
*   Перечисление кодов ошибок, которые функции работы со стаком возвращают.  
*/
enum RETURN_CODES
{
    STACK_OK =                  0x00000000,     // Все ОК.
    STACK_MEM_ALLOCK_ERR =      0x00000001,     // Ошибка аллоцирования / реаллоцирования памяти.
    STACK_INCREASE_ERR =        0x00000002,     // Ошибка в функции увеличения размера стека.
    STACK_DECREASE_ERR =        0x00000003,     // Ошибка в функции уменьшения размера стека.
    STACK_CTOR_DBL_CALL =       0x00000004,     // Двойной вызов конструктора.
    STACK_DTOR_DBL_CALL =       0x00000005,     // Двойной вызов деструктора.
    STACK_INCORRECT_DATA_PTR =  0x00000006,     //  Неверный указатель на данные.
    STACK_WRONG_START_HUMMINGBIRD = 0x00000007,  //  Неверная начальная канарейка.
    STACK_WRONG_END_HUMMINGBIRD = 0x00000008,  //  Неверная конечная канарейка.
    STACK_INCORRECT_SIZE = 0x00000009,  //  Неверный размер стека.
    STACK_INCORRECT_CAPACITY = 0x00000010,  //  Неверный размер стека.
    STACK_WRONG_HASH_SUM = 0x00000011,  //  Неверный размер стека.
};

/**
*   Перечисление функций для отладки.  
*/
enum FUNC_CODES
{
    STACK_CTOR_CODE  =           0x00000100,
    STACK_DTOR_CODE =            0x00000200,
    STACK_PUSH_CODE =            0x00000300,
    STACK_POP_CODE =             0x00000400,
    STACK_INCREASE_CODE =        0x00000500,
    STACK_DECREASE_CODE =        0x00000600,
    STACK_DUMP_CODE =            0x00000700,
    UNIT_TEST_CODE =             0x00000800
};

/**
*   Перечисление отравляющих констант.  
*/
enum POISONS
{
    STACK_DATA_POISON = 0xDEAD // Отравление данных.
};

//flexxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

/**
*   @brief Функция StackCtorFunc конструирует объект стека.
*   
*   @param [in, out] stack  Указатель на структуру \link Stack \endlink.
*   @param [in] size        Начальный размер для аллоцирования буффера.
*   @param [in] stack_name  Имя переменной стека.
*   @param [in] line        Строка, в которой был вызван конструктор.
*   @param [in] func_name   Имя функции, в которой был вызван конструктор.
*   @param [in] file_name   Имя файла, в котором был вызван конструктор.
*   @return Один из кодов \link RETURN_CODES \endlink.
*/
int StackCtorFunc (Stack* stack, size_t size, const char* stack_name, const char* func_name, int line, const char* file_name);

//flexxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

/**
*   @brief Функция StackDtor уничтожает объект стака.
*   
*   @param [in] stack Указатель на структуру \link Stack \endlink.
*   @return Один из кодов \link RETURN_CODES \endlink.
*/
int StackDtor (Stack* stack);

//flexxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

/**
*   @brief Функция SetStackPrinterFunc уничтожает объект стака.
*   @param [in] stack Указатель на структуру \link Stack \endlink.
*   @param [in] printer_func Указатель на функцию для распечатки значений.
*   @return Один из кодов \link RETURN_CODES \endlink.
*/
int SetStackPrinterFunc (Stack* stack, void (*printer_func)(stack_type*));

//flexxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

/**
*   @brief Функция StackPush пушит элемент в стак.
*   
*   @param [in, out] stack Указатель на структуру \link Stack \endlink.
*   @param [in] element Элемент для пуша.
*   @return Один из кодов \link RETURN_CODES \endlink.
*/
int StackPush (Stack* stack, stack_type element);

//flexxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

/**
*   @brief Функция StackPush попит элемент из стака.
*   
*   @param [in, out] stack Указатель на структуру \link Stack \endlink.
*   @param [out] out_element Указатель на переменную, в котрую будет сохранено полученное значение.
*   @return Один из кодов \link RETURN_CODES \endlink.
*/
int StackPop (Stack* stack, stack_type* out_element);

//flexxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

/**
*   @brief Функция StackIncrease увеличивает стак при необходимости.
*   
*   @param [in, out] stack Указатель на структуру \link Stack \endlink.
*   @return Один из кодов \link RETURN_CODES \endlink.
*/
int StackIncrease (Stack* stack);

//flexxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

/**
*   @brief Функция StackDecrease уменьшает стак при необходимости.
*   
*   @param [in, out] stack Указатель на структуру \link Stack \endlink.
*   @return Один из кодов \link RETURN_CODES \endlink.
*/
int StackDecrease (Stack* stack);

//flexxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

/**
*   @brief Функция StackDumpFunction выводит отладочную информацию о стаке.
*   
*   @param [in, out] stack Указатель на структуру \link Stack \endlink.
*   @param [in] print_function Указатель на функцию для печати одного элемента стека. 
*   @param [in] line Номер строки, в которой вызвана данная функция.
*   @param [in] func_name Имя функции, в которой вызвана данная функция.
*   @param [in] file_name Имя файла, из которого вызвана данная функция.
*   @return Один из кодов \link RETURN_CODES \endlink.
*/
int StackDumpFunc (Stack* stack, const int line, const char* func_name, const char* file_name, const char* stack_name);

//flexxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

/**
*   @brief Функция StackValidate проверяет, что со стеком все хорошо.
*   
*   @param [in, out] stack Указатель на структуру \link Stack \endlink.
*   @return Один из кодов \link RETURN_CODES \endlink.
*/
int StackValidate (Stack* stack, const int func_code);

//flexxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

/**
*   @brief Функция HashSum считает универсальную хэш-сумму.
*   
*   @param [in] ptr Указатель на объект.
*   @param [in] size Размер объекта.
*   @return Хэш-сумму.
*/
unsigned long long HashSum(void* ptr, size_t size, unsigned long long hash = 0);

//flexxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

/**
*   @brief Функция StackHashSum считает хэш-сумму стека.
*   
*   @param [in] stack Указатель на структуру \link Stack \endlink.
*   @return Хэш-сумму стека.
*/
unsigned long long StackHashSum(Stack* stack);

//flexxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

/**
*   @brief Функция StackPrintExitCode .
*   
*   @param [in] err_and_func_code Переменная, содержащая код функции и ошибки.
*/
int StackPrintExitCode(int err_and_func_code);

/**
*   @brief Функция UnitTest проводит тестирование стака.
*/
int UnitTest ();

//flexxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

/** @file
 * @author Асаян А.В.
 * @version 0.1
 * @date 2019-2019
 * @copyright ИБСТ ПГУ
 * @warning Курсовая работа
 * @brief Заголовочный файл для модуля LFSR
 */
#include <string>
#include <iostream>
#include <cstdint>
#pragma once
using namespace std;
/** @brief Класс-исключение.
 */
class LFSR_error: public std::invalid_argument
{
public:
    explicit LFSR_error (const std::string& what_arg):
        std::invalid_argument(what_arg) {}
    explicit LFSR_error (const char* what_arg):
        std::invalid_argument(what_arg) {}
};
/** @brief Генератор на базе регистра сдвига линейной обратной связи.
 * @details Начальное заполнение регистра устанавливается в конструкторе.
 * Для преобразования полинома в последовательность отводных битов используется метод Polynomial_Converter.
 * Для генерации случайного числа используется метод LFSR_Galois.
 */
class LFSR
{
private:
    int64_t Seed=1;///< Начальное заполнение регистра.
    string getValidPolynomial(const string poli);///< Метод проверки полинома, задающего отводные биты.
    int64_t getValidSeed(const int64_t seed);///< Метод проверки начального заполнения регистра.
public:
/**
 * @brief Конструктор для установки начального заполнения регистра.
 * @param [in] n Начальное заполнение регистра.
 * @warning Начальное заполнение регистра не должно быть больше 9223372036854775807.
 * @throw LFSR_error, если число отрицательное, равно 0 или больше 9223372036854775807, или не является числом.
 */
    LFSR(int64_t n);
/**
 * @brief Метод генерирующий псевдослучайное число.
 * @param [in] branch Биты отвода.
 * @return Случайное число.
 */
    uint64_t LFSR_Galois (uint64_t branch);
/**
 * @brief Метод для конвертации строки-полинома в последовательность битов отвода.
 * @details Превращает стрроку-полином в число, в двоичной записи этого числа единичные биты обозначают степени числа x введённого полинома.
 * @param [in] poli Строка-полином.Полином должен быть в степени 64, степени должны быть строго расставлены в порядке убывания от большей к меньшей. Использовать строго знак +.Вид полинома x^64+x^32+1.
 * @warning Полином должен быть задан строго по правилам, иначе будет вызвано исключение.
 * @throw LFSR_error, если строка-полином введён неверно.
 */
    uint64_t Polynomial_Converter(string poli);
    
};

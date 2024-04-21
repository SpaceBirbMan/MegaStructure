#pragma once
#include "HeavyIronWell.h"
#include <iostream>
#include <regex>
#include <string>

/// <summary>
/// Класс стекового калькулятора
/// </summary>
class Ladder3
{
private:
    HIWell<double> stack;
    std::string expression;

public:
    class PostFix
    {
    private:
        HIWell<double>& parrent; // Ссылка на объект HIWell<std::string>
        std::string expression;
    public:
        PostFix(HIWell<double>& in_parrent, std::string expr) : parrent(in_parrent), expression(expr) { }

        /// <summary>
        /// Считает выражение
        /// </summary>
        /// <returns> число либо nan (в случае кривого выражения) </returns>
        double calculate() {
            std::istringstream iss(expression);
            std::string token;

            while (iss >> token) {
                if (std::isdigit(token[0]) || (token[0] == '-' && std::isdigit(token[1]))) { // Если токен - число
                    parrent.push(std::stod(token)); // Помещаем число в стек
                }
                else if (token.size() == 1 && (token[0] == '+' || token[0] == '-' || token[0] == '*' || token[0] == '/')) { // Если токен - оператор
                    if (parrent.isEmpty()) {
                        std::cerr << "Invalid expression: Too few operands" << std::endl;
                        return std::numeric_limits<double>::quiet_NaN(); // Возвращаем NaN в случае ошибки
                    }
                    double operand2 = parrent.pull();
                    if (parrent.isEmpty()) {
                        std::cerr << "Invalid expression: Too few operands" << std::endl;
                        return std::numeric_limits<double>::quiet_NaN(); // Возвращаем NaN в случае ошибки
                    }
                    double operand1 = parrent.pull();
                    double result;

                    switch (token[0]) {
                    case '+':
                        result = operand1 + operand2;
                        break;
                    case '-':
                        result = operand1 - operand2;
                        break;
                    case '*':
                        result = operand1 * operand2;
                        break;
                    case '/':
                        if (operand2 == 0) {
                            std::cerr << "Invalid expression: Division by zero" << std::endl;
                            return std::numeric_limits<double>::quiet_NaN(); // Возвращаем NaN в случае ошибки
                        }
                        result = operand1 / operand2;
                        break;
                    default:
                        throw std::runtime_error("Invalid operator");
                    }

                    parrent.push(result); // Помещаем результат обратно в стек
                }
            }

            // Проверяем, осталось ли что-то в стеке
            if (parrent.isEmpty()) {
                std::cerr << "Invalid expression: Too few operands" << std::endl;
                return std::numeric_limits<double>::quiet_NaN(); // Возвращаем NaN в случае ошибки
            }

            // Возвращаем результат, который остался в стеке
            return parrent.pull();
        }

    };

public:
    /// <summary>
    /// Инициализация калькулятора
    /// </summary>
    Ladder3() {}

    /// <summary>
    /// Инициализация постфиксной надстройки
    /// </summary>
    /// <returns></returns>
    PostFix postfix() { return PostFix(stack, expression); }

    /// <summary>
    /// Устанавливает выражение
    /// </summary>
    /// <param name="expr"> строка с выражением </param>
    void setExpression(std::string expr) { expression = expr; }
};

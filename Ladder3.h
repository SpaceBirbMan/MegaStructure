//#pragma once
//#include "IronWell.h"
//#include <iostream>
//#include <regex>
//#include <string>
//
//class Ladder3
//{
//private:
//    IronWell<std::string> stack;
//    std::string expression;
//
//    class PostFix
//    {
//    private: 
//        IronWell<std::string> parrent;
//        std::string expression;
//    public:
//
//        PostFix(IronWell<std::string> in_parrent, std::string expr) : parrent(in_parrent), expression(expr) { }
//
//        bool check()
//        {
//            std::regex pattern_d("^-?\\d*\\.?\\d+$");
//            std::regex pattern_op("[+\\-*/\\^]");
//
//            std::istringstream iss(expression);
//            std::string token;
//
//            size_t counter = 0;
//
//            while (iss >> token)
//            {
//                if (counter % 2 == 0)
//                {
//                    if (std::regex_match(token, pattern_d))
//                        counter++;
//                    else
//                    {
//                        std::cerr << "Invalid expression: Unexpected operand" << std::endl;
//                        return false;
//                    }
//                }
//                else
//                {
//                    if (std::regex_match(token, pattern_op))
//                        counter++;
//                    else
//                    {
//                        std::cerr << "Invalid expression: Unexpected operator" << std::endl;
//                        return false;
//                    }
//                }
//            }
//
//            if (counter != 3)
//            {
//                std::cerr << "Invalid expression: Incorrect number of operands and operators" << std::endl;
//                return false;
//            }
//
//            return true;
//        }
//
//        double calculate()
//        {
//            if (!check()) // Проверяем, что выражение корректно
//                throw std::runtime_error("Invalid expression");
//
//            std::istringstream iss(expression);
//            std::string token;
//
//            while (iss >> token)
//            {
//                if (std::regex_match(token, std::regex("^-?\\d*\\.?\\d+$"))) // Если токен - операнд, помещаем его в стек
//                {
//                    parrent.push(token);
//                }
//                else // Если токен - оператор, берем два последних операнда из стека, выполняем операцию и помещаем результат в стек
//                {
//                    double operand2 = std::stod(parrent.pull());
//                    double operand1 = std::stod(parrent.pull());
//                    double result;
//
//                    switch (token[0])
//                    {
//                    case '+':
//                        result = operand1 + operand2;
//                        break;
//                    case '-':
//                        result = operand1 - operand2;
//                        break;
//                    case '*':
//                        result = operand1 * operand2;
//                        break;
//                    case '/':
//                        if (operand2 == 0)
//                            throw std::runtime_error("Division by zero");
//                        result = operand1 / operand2;
//                        break;
//                    default:
//                        throw std::runtime_error("Invalid operator");
//                    }
//
//                    parrent.push(std::to_string(result)); // Помещаем результат обратно в стек как строку
//                }
//            }
//
//            return std::stod(parrent.pull()); // Возвращаем результат, который остался в стеке
//        }
//
//    };
//
//    class InFix
//    {
//    public:
//        bool check()
//        {
//            // Проверка соответствия типа и структуры
//            // Возвращает true, если соответствует, иначе false
//        }
//
//        double calculate()
//        {
//            // Проверка соответствия и выполнение вычислений
//        }
//    };
//
//    class PreFix
//    {
//    public:
//        bool check()
//        {
//            // Проверка соответствия типа и структуры
//            // Возвращает true, если соответствует, иначе false
//
//            
//        }
//
//        double calculate()
//        {
//            // Проверка соответствия и выполнение вычислений
//        }
//    };
//
//public:
//    Ladder3(size_t input_size)
//    {
//        size_t stack_size = input_size * 5 / input_size;
//        stack = IronWell<std::string>();
//        
//    }
//
//    PreFix prefix() { return PreFix(); }
//    PostFix postfix() { return PostFix(expression, stack.getSize()); }
//    InFix infix() { return InFix(); }
//
//    void setExpression(std::string expr) { expression = expr; }
//    size_t stackSize() const { return stack.getSize(); }
//};

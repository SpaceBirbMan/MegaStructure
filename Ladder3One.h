#pragma once
#include "HeavyIronWell.h"
#include <iostream>
#include <regex>
#include <string>

/// <summary>
/// ����� ��������� ������������
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
        HIWell<double>& parrent; // ������ �� ������ HIWell<std::string>
        std::string expression;
    public:
        PostFix(HIWell<double>& in_parrent, std::string expr) : parrent(in_parrent), expression(expr) { }

        /// <summary>
        /// ������� ���������
        /// </summary>
        /// <returns> ����� ���� nan (� ������ ������� ���������) </returns>
        double calculate() {
            std::istringstream iss(expression);
            std::string token;

            while (iss >> token) {
                if (std::isdigit(token[0]) || (token[0] == '-' && std::isdigit(token[1]))) { // ���� ����� - �����
                    parrent.push(std::stod(token)); // �������� ����� � ����
                }
                else if (token.size() == 1 && (token[0] == '+' || token[0] == '-' || token[0] == '*' || token[0] == '/')) { // ���� ����� - ��������
                    if (parrent.isEmpty()) {
                        std::cerr << "Invalid expression: Too few operands" << std::endl;
                        return std::numeric_limits<double>::quiet_NaN(); // ���������� NaN � ������ ������
                    }
                    double operand2 = parrent.pull();
                    if (parrent.isEmpty()) {
                        std::cerr << "Invalid expression: Too few operands" << std::endl;
                        return std::numeric_limits<double>::quiet_NaN(); // ���������� NaN � ������ ������
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
                            return std::numeric_limits<double>::quiet_NaN(); // ���������� NaN � ������ ������
                        }
                        result = operand1 / operand2;
                        break;
                    default:
                        throw std::runtime_error("Invalid operator");
                    }

                    parrent.push(result); // �������� ��������� ������� � ����
                }
            }

            // ���������, �������� �� ���-�� � �����
            if (parrent.isEmpty()) {
                std::cerr << "Invalid expression: Too few operands" << std::endl;
                return std::numeric_limits<double>::quiet_NaN(); // ���������� NaN � ������ ������
            }

            // ���������� ���������, ������� ������� � �����
            return parrent.pull();
        }

    };

public:
    /// <summary>
    /// ������������� ������������
    /// </summary>
    Ladder3() {}

    /// <summary>
    /// ������������� ����������� ����������
    /// </summary>
    /// <returns></returns>
    PostFix postfix() { return PostFix(stack, expression); }

    /// <summary>
    /// ������������� ���������
    /// </summary>
    /// <param name="expr"> ������ � ���������� </param>
    void setExpression(std::string expr) { expression = expr; }
};

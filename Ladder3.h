#pragma once
#include "IronWell.h"
#include <iostream>
#include <regex>

class Ladder3
{
private:
    IronWell<std::string> memory;

    class PostFix
    {
    private: 
        IronWell<std::string> parrent;
    public:

        PostFix(IronWell<std::string> in_parrent) : parrent(in_parrent) { }

        bool check()
        {
            // ѕроверка соответстви€ типа и структуры
            // ¬озвращает true, если соответствует, иначе false


            IronWell<std::string> tmp(parrent);

            std::regex pattern_d("^-?\\d*\\.?\\d+$");
            std::regex pattern_op("+|-|/|*|(**)");

            size_t sz = parrent.getSize();
            size_t counter = 0;
            if ((sz - 1) % 2 == 0 || sz == 3)
                for (int i = 0; i < sz; i++)
                {
                    std::string s = tmp.push();
                    if (i == sz - 1) counter = 3;
                    switch (counter)
                    {
                    case 0: { /*намеренно скипаем */ }
                    case 1:
                    {
                        if (std::regex_match(s, pattern_d))
                            counter++;
                        else std::cerr << "wrong stack expression" << std::endl;
                        break;
                    }
                    case 2: 
                    { 
                        if (std::regex_match(s, pattern_op))
                            counter = 0;
                        else std::cerr << "wrong stack expression" << std::endl;
                        break; 
                    }
                    case 3:
                    {
                        if (std::regex_match(s, pattern_op))
                            return true;
                        else std::cerr << "wrong stack expression" << std::endl;
                    }
                    default: return false;
                    }
                }
            else return false;
            return false;
        }

        double calculate()
        {
            check();
        }
    };

    class InFix
    {
    public:
        bool check()
        {
            // ѕроверка соответстви€ типа и структуры
            // ¬озвращает true, если соответствует, иначе false
        }

        double calculate()
        {
            // ѕроверка соответстви€ и выполнение вычислений
        }
    };

    class PreFix
    {
    public:
        bool check()
        {
            // ѕроверка соответстви€ типа и структуры
            // ¬озвращает true, если соответствует, иначе false

            
        }

        double calculate()
        {
            // ѕроверка соответстви€ и выполнение вычислений
        }
    };

public:
    Ladder3() {}
    Ladder3(IronWell<std::string> stack) : memory(stack) {}

    PreFix prefix() { return PreFix(); }
    PostFix postfix() { return PostFix(memory); }
    InFix infix() { return InFix(); }

    void setStack(IronWell<std::string> stack) { memory = stack; }
    IronWell<std::string> getStack() { return memory; }
};

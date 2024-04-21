#pragma once
#include "Chain2.h"

template <typename TYPE>
class HIWell
{
private:
    Link<TYPE>* last;
    Chain2<TYPE> stack;
    size_t stack_size = 0;
public:
    /// <summary>
    /// ������������� ������� �����
    /// </summary>
    HIWell() : last(nullptr) {}

    //HIWell(size_t size)
    //{
    //    stack_size = 0;
    //}

    /// <summary>
    /// ���������� � ����
    /// </summary>
    /// <param name="data"> ������� </param>
    void push(TYPE data)
    {
        stack.adder.back(data); // ���������� ������ �������� � ����
        last = stack.getLast();
    }

    /// <summary>
    /// ����������� �������� �� ������
    /// </summary>
    /// <returns> ������� </returns>
    TYPE pull()
    {
        if (stack.isEmpty())
            throw std::out_of_range("Stack is empty");

        TYPE res = last->getData();
        stack.deleter.back(); // �������� ���������� �������� �� �����
        last = stack.getLast();
        return res;
    }

    /// <summary>
    /// ��������� ������ �����
    /// </summary>
    /// <returns> ������ </returns>
    size_t getSize() const { return stack.getSize(); }

    /// <summary>
    /// ������� ����
    /// </summary>
    void clear()
    {
        stack.clear();
        last = nullptr;
    }

    /// <summary>
    /// ���������� ��������� ������� �����, �� ������ ��� �� ����
    /// </summary>
    /// <returns></returns>
    TYPE peak() // ��������� �������� �������� �������� ����� ��� ��� ��������
    {
        if (last != nullptr)
            return last->getData();
        else
            throw std::out_of_range("Stack is empty");
    }

    /// <summary>
    /// ���� �� ������
    /// </summary>
    /// <returns> true/false </returns>
    bool isEmpty() { return stack.isEmpty(); }
};

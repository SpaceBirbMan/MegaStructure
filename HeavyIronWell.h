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
    /// Инициализация пустого стека
    /// </summary>
    HIWell() : last(nullptr) {}

    //HIWell(size_t size)
    //{
    //    stack_size = 0;
    //}

    /// <summary>
    /// Добавление в стек
    /// </summary>
    /// <param name="data"> элемент </param>
    void push(TYPE data)
    {
        stack.adder.back(data); // Добавление нового элемента в стек
        last = stack.getLast();
    }

    /// <summary>
    /// Вытянивание элемента из списка
    /// </summary>
    /// <returns> элемент </returns>
    TYPE pull()
    {
        if (stack.isEmpty())
            throw std::out_of_range("Stack is empty");

        TYPE res = last->getData();
        stack.deleter.back(); // Удаление последнего элемента из стека
        last = stack.getLast();
        return res;
    }

    /// <summary>
    /// Возращает размер стека
    /// </summary>
    /// <returns> размер </returns>
    size_t getSize() const { return stack.getSize(); }

    /// <summary>
    /// Очищает стек
    /// </summary>
    void clear()
    {
        stack.clear();
        last = nullptr;
    }

    /// <summary>
    /// Возвращает последний элемент стека, не удаляя его из него
    /// </summary>
    /// <returns></returns>
    TYPE peak() // Получение значения верхнего элемента стека без его удаления
    {
        if (last != nullptr)
            return last->getData();
        else
            throw std::out_of_range("Stack is empty");
    }

    /// <summary>
    /// Пуст ли список
    /// </summary>
    /// <returns> true/false </returns>
    bool isEmpty() { return stack.isEmpty(); }
};

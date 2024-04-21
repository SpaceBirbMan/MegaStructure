//#pragma once
//#include "Interface.h"
//
////Неприоритетно
//
///// <summary>
///// Класс кастомного стека
///// </summary>
//template <typename TYPE>
//class Level : public Node<TYPE>
//{
//private:
//	TYPE data;
//	Level<TYPE>* prev;
//
//public:
//	Level() : prev(nullptr) {}
//	Level(TYPE data) : data(data), prev(nullptr) {}
//
//	TYPE getData() const override { return data; }
//	void setData(TYPE data) override { this->data = data; }
//
//	Level<TYPE>* getPrev() { return prev; }
//	void setPrev(Level<TYPE>* prev) { this->prev = prev; }
//    std::string toString() override { return ""; }
//};
//
//template<typename TYPE>
//class IronWell : public CustomStack<TYPE> 
//{
//private:
//    size_t stack_size = 0;
//    Level<TYPE>* last = nullptr;
//
//    void add(TYPE data, size_t index = 0) override
//    {
//        Level<TYPE>* next = new Level<TYPE>(data);
//        next->setPrev(last);
//        last = next;
//        ++stack_size;
//    }
//
//    void remove() override
//    {
//        if (last == nullptr)
//            return;
//
//        Level<TYPE>* tmp = last;
//        last = last->getPrev();
//        delete tmp;
//        --stack_size;
//    }
//
//public:
//    IronWell() {}
//    IronWell(TYPE data)
//    {
//        last = new Level<TYPE>(data);
//        ++stack_size;
//    }
//
//    ~IronWell()
//    {
//        while (last != nullptr)
//        {
//            Level<TYPE>* tmp = last;
//            last = last->getPrev();
//            delete tmp;
//        }
//    }
//
//    TYPE pull() override
//    {
//        if (last == nullptr)
//            throw std::out_of_range("Stack is empty");
//
//        TYPE res = last->getData();
//        remove();
//        return res;
//    }
//
//    void push(TYPE data) override
//    {
//        add(data);
//    }
//
//    size_t getSize() override { return stack_size; }
//
//    std::string toString() override
//    {
//        //std::string result;
//        //Level<TYPE>* current = last;
//        //while (current != nullptr)
//        //{
//        //    result += std::to_string(current->getData()) + " ";
//        //    current = current->getPrev();
//        //}
//        //return result;
//        return "";
//    }
//
//    IronWell(const IronWell& other) : stack_size(other.stack_size), last(nullptr) {
//        // Копируем элементы из другого стека
//        if (other.last != nullptr) {
//            last = new Level<TYPE>(*other.last);
//            Level<TYPE>* current = last;
//            Level<TYPE>* other_current = other.last->getPrev();
//            while (other_current != nullptr) {
//                current->setPrev(new Level<TYPE>(*other_current));
//                current = current->getPrev();
//                other_current = other_current->getPrev();
//            }
//        }
//    }
//
//    IronWell& operator=(const IronWell& other) {
//        if (this != &other) { // Проверка на самоприсваивание
//            // Удаляем текущие элементы
//            while (last != nullptr) {
//                Level<TYPE>* tmp = last;
//                last = last->getPrev();
//                delete tmp;
//            }
//            stack_size = other.stack_size;
//            last = nullptr;
//            // Копируем элементы из другого стека
//            if (other.last != nullptr) {
//                last = new Level<TYPE>(*other.last);
//                Level<TYPE>* current = last;
//                Level<TYPE>* other_current = other.last->getPrev();
//                while (other_current != nullptr) {
//                    current->setPrev(new Level<TYPE>(*other_current));
//                    current = current->getPrev();
//                    other_current = other_current->getPrev();
//                }
//            }
//        }
//        return *this;
//    }
//
//    IronWell(IronWell&& other) noexcept : stack_size(other.stack_size), last(other.last) {
//        other.stack_size = 0;
//        other.last = nullptr;
//    }
//
//    IronWell& operator=(IronWell&& other) noexcept {
//        if (this != &other) { // Проверка на самоприсваивание
//            // Удаляем текущие элементы
//            while (last != nullptr) {
//                Level<TYPE>* tmp = last;
//                last = last->getPrev();
//                delete tmp;
//            }
//            stack_size = other.stack_size;
//            last = other.last;
//            other.stack_size = 0;
//            other.last = nullptr;
//        }
//        return *this;
//    }
//
//    void setSize(size_t size)
//    {
//        stack_size = size;
//
//    }
//
//};

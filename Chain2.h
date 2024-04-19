#pragma once

#include <iostream>
#include <sstream>
#include "Interface.h"

/// <summary>
/// Класс звена списка
/// </summary>
/// <typeparam name="TYPE"></typeparam>
template <typename TYPE>
class Link : public Node<TYPE>
{
private:
    TYPE data;
    Link<TYPE>* next;
    Link<TYPE>* prev;
    size_t index = 0;

public:
    Link(TYPE value) : data(value), next(nullptr), prev(nullptr) {}

    void setData(TYPE value) override
    {
        this->data = value;
    }

    TYPE getData() const override
    {
        return this->data;
    }

    std::string toString() override
    {
        std::stringstream ss;
        ss << data;
        return ss.str();
    }

    Link<TYPE>* getNext() { return this->next; }
    Link<TYPE>* getPrev() { return this->prev; }
    void setNext(Link<TYPE> next) { this->next = next; }
    void setPrev(Link<TYPE> prev) { this->prev = prev; }
    size_t getIndex() { return index; }
    void setIndex(size_t index) { this->index = index; }
};


/// <summary>
/// Класс для создания и работы со связным списком
/// </summary>
/// <typeparam name="TYPE"></typeparam>
template <typename TYPE>
class Chain2 : public AList<TYPE> {
private:
    size_t chain_size = 0;
    Link<TYPE>* current_link = nullptr;
    Link<TYPE>* first_link = nullptr;
    Link<TYPE>* last_link = nullptr;

    // Класс для добавления элементов
    class NodeAdder {
    private:
        Chain2<TYPE>* chain;

    public:
        NodeAdder(Chain2<TYPE>* chain) : chain(chain) {}

        void front(TYPE value) {
            chain->toStart();
            chain->add(value);
        }

        void back(TYPE value) {
            chain->toEnd();
            chain->add(value);
        }

        void at(size_t index, TYPE value) {
            chain->seek(index);
            chain->add(value);
        }
    };

    // Класс для удаления элементов
    class NodeDeleter {
    private:
        Chain2<TYPE>* chain;

    public:
        NodeDeleter(Chain2<TYPE>* chain) : chain(chain) {}

        void front() {
            chain->toStart();
            chain->remove();
        }

        void back() {
            chain->toEnd();
            chain->remove();
        }

        void at(size_t index) {
            chain->seek(index);
            chain->remove();
        }
    };

    NodeAdder adder{ this }; // Объект для добавления элементов
    NodeDeleter deleter{ this }; // Объект для удаления элементов

    void add(TYPE value) override {
        Link<TYPE>* insert = new Link<TYPE>(value);
        insert->setNext(current_link->getNext());
        insert->setPrev(current_link);
        if (current_link->getNext() != nullptr) {
            current_link->getNext()->setPrev(insert);
        }
        current_link->setNext(insert);
        chain_size++;

        // Обновление last_link, если добавленный элемент становится последним
        if (insert->getNext() == nullptr) {
            last_link = insert;
        }
    }

    void remove(TYPE value) override {
        if (current_link == nullptr) {
            return;
        }
        Link<TYPE>* tmp = current_link;
        if (current_link->getPrev() != nullptr) {
            current_link->getPrev()->setNext(current_link->getNext());
        }
        if (current_link->getNext() != nullptr) {
            current_link->getNext()->setPrev(current_link->getPrev());
        }
        delete tmp;
        chain_size--;

        // Обновление last_link, если удаленный элемент был последним
        if (tmp == last_link) {
            last_link = tmp->getPrev();
        }
    }

public:
    Chain2() {}

    Chain2(TYPE value) : chain_size(1) {
        current_link = new Link<TYPE>(value);
        first_link = current_link;
        last_link = current_link;
    }

    // Остальные методы класса...

    // Реализация правила пяти
    ~Chain2() {
        clear();
    }

    Chain2(const Chain2& other) : chain_size(other.chain_size) {
        // Копирование элементов
        Link<TYPE>* other_current = other.first_link;
        while (other_current != nullptr) {
            add(other_current->getData());
            other_current = other_current->getNext();
        }
    }

    Chain2& operator=(const Chain2& other) {
        if (this != &other) {
            clear(); // Очищаем текущий список
            chain_size = other.chain_size;
            // Копируем элементы
            Link<TYPE>* other_current = other.first_link;
            while (other_current != nullptr) {
                add(other_current->getData());
                other_current = other_current->getNext();
            }
        }
        return *this;
    }

    Chain2(Chain2&& other) noexcept : chain_size(other.chain_size), current_link(other.current_link), first_link(other.first_link), last_link(other.last_link) {
        other.chain_size = 0;
        other.current_link = nullptr;
        other.first_link = nullptr;
        other.last_link = nullptr;
    }

    Chain2& operator=(Chain2&& other) noexcept {
        if (this != &other) {
            clear(); // Очищаем текущий список
            chain_size = other.chain_size;
            current_link = other.current_link;
            first_link = other.first_link;
            last_link = other.last_link;

            other.chain_size = 0;
            other.current_link = nullptr;
            other.first_link = nullptr;
            other.last_link = nullptr;
        }
        return *this;
    }


    size_t getSize() const override { return chain_size; }

    void right() { current_link = current_link->getNext(); }
    void left() { current_link = current_link->getPrev(); }

    void seek(size_t index)
    {
       bool mode = false;
       if (index >= chain_size && index < 0)
           if (index >= current_link) mode = true; else mode = false;
       while (index != current_link->getIndex())
           if (mode) right(); else left();
    }

    void toStart() { current_link = first_link; }
    void toEnd() { current_link = last_link; }

    void ring() 
    { 
        if (last_link->getNext() != nullptr && first_link->getPrev() != nullptr)
        {
            first_link->setPrev(last_link);
            last_link->setNext(first_link);
        }
        else
        {
            first_link->setPrev(nullptr);
            last_link->setNext(nullptr);
        }
    }

    // Сортировка списка (пузырьковая сортировка)
    void sort() {
        if (chain_size <= 1) {
            return;
        }

        bool swapped;
        do {
            swapped = false;
            Link<TYPE>* ptr = first_link;
            while (ptr->getNext() != nullptr) {
                if (ptr->getData() > ptr->getNext()->getData()) {
                    std::swap(ptr->getData(), ptr->getNext()->getData());
                    swapped = true;
                }
                ptr = ptr->getNext();
            }
        } while (swapped);
    }

    // Поиск элемента в списке
    bool search(TYPE value) {
        Link<TYPE>* ptr = first_link;
        while (ptr != nullptr) {
            if (ptr->getData() == value) {
                return true;
            }
            ptr = ptr->getNext();
        }
        return false;
    }

    // Конкатенация списка с другим списком
    void concatenate(Chain2& other) {
        if (other.getSize() == 0) {
            return;
        }

        if (chain_size == 0) {
            first_link = other.first_link;
            last_link = other.last_link;
            chain_size = other.chain_size;
        }
        else {
            last_link->setNext(other.first_link);
            other.first_link->setPrev(last_link);
            last_link = other.last_link;
            chain_size += other.chain_size;
        }

        other.chain_size = 0;
        other.first_link = nullptr;
        other.last_link = nullptr;
    }

    // Разделение списка на два по указанному индексу
    void divide(size_t index, Chain2& secondList) {
        if (index >= chain_size) {
            return;
        }

        Link<TYPE>* ptr = first_link;
        size_t count = 0;
        while (count < index) {
            ptr = ptr->getNext();
            count++;
        }

        secondList.first_link = ptr->getNext();
        secondList.last_link = last_link;
        secondList.chain_size = chain_size - index;

        last_link = ptr;
        last_link->setNext(nullptr);
        chain_size = index;
    }

    // Очистка списка
    void clear() {
        Link<TYPE>* current = first_link;
        while (current != nullptr) {
            Link<TYPE>* next = current->getNext();
            delete current;
            current = next;
        }
        first_link = nullptr;
        last_link = nullptr;
        chain_size = 0;
    }

    Link<TYPE>* getCurrent() { return current_link; }
    Link<TYPE>* getLast() { return last_link; }
    Link<TYPE>* getFirst() { return first_link; }

    //Надо реализовать правило пяти
    //Добавить конвертацию в массив, можно в s1605 и обратно
};

#pragma once
#include <iostream>
#include <sstream>
#include <vector>
//#include "Interface.h"

/// <summary>
/// Класс звена цепи (списка)
/// </summary>
/// <typeparam name="TYPE"></typeparam>
template <typename TYPE>
class Link
{
private:
    TYPE data;
    Link<TYPE>* next;
    Link<TYPE>* prev;
    size_t index = 0;

public:
    Link(TYPE value) : data(value), next(nullptr), prev(nullptr) {}

    void setData(TYPE value) /*override*/
    {
        this->data = value;
    }

    TYPE getData() const /*override*/
    {
        return this->data;
    }

    std::string toString() /*override*/
    {
        std::stringstream ss;
        ss << data;
        return ss.str();
    }

    /// <summary>
    /// Возвращает указатель на следующий элемент
    /// </summary>
    /// <returns> указатель на звено </returns>
    Link<TYPE>* getNext() { return this->next; }

    /// <summary>
    /// Возвращает указатель на предыдущий элемент
    /// </summary>
    /// <returns> указатель на звено </returns>
    Link<TYPE>* getPrev() { return this->prev; }

    /// <summary>
    /// Устанавливает указатель на следующий элемент
    /// </summary>
    /// <param name="next"> указатель на звено </param>
    void setNext(Link<TYPE>* next) { this->next = next; }

    /// <summary>
    /// Устанавливает указатель на предыдущий элемент
    /// </summary>
    /// <param name="prev"> указатель на звено </param>
    void setPrev(Link<TYPE>* prev) { this->prev = prev; }

    /// <summary>
    /// Возвращает индекс звена
    /// </summary>
    /// <returns> индекс звена </returns>
    size_t getIndex() { return index; }

    /// <summary>
    /// Устанавливает индекс звену
    /// </summary>
    /// <param name="index"> индекс типа size_t </param>
    void setIndex(size_t index) { this->index = index; }
};

/// <summary>
/// Класс цепи(списка)
/// </summary>
/// <typeparam name="TYPE"></typeparam>
template <typename TYPE>
class Chain2
{
private:
    size_t chain_size = 0;
    Link<TYPE>* current_link = nullptr;
    Link<TYPE>* first_link = nullptr;
    Link<TYPE>* last_link = nullptr;

    /// <summary>
    /// Добавление элементов
    /// </summary>
    class NodeAdder {
    private:
        Chain2<TYPE>* chain;

    public:
        NodeAdder(Chain2<TYPE>* chain) : chain(chain) {}

        /// <summary>
        /// Добавить в начало
        /// </summary>
        /// <param name="value"> элемент </param>
        void front(TYPE value) {
            Link<TYPE>* newLink = new Link<TYPE>(value);
            if (chain->isEmpty()) {
                chain->first_link = newLink;
                chain->last_link = newLink;
            }
            else {
                newLink->setNext(chain->first_link);
                chain->first_link->setPrev(newLink);
                chain->first_link = newLink;
            }
            updateIndexes(chain->first_link);
            chain->chain_size++;
        }

        /// <summary>
        /// Добавить в конец
        /// </summary>
        /// <param name="value"> элемент </param>
        void back(TYPE value) {
            Link<TYPE>* newLink = new Link<TYPE>(value);
            if (chain->isEmpty()) {
                chain->first_link = newLink;
                chain->last_link = newLink;
            }
            else {
                chain->last_link->setNext(newLink);
                newLink->setPrev(chain->last_link);
                chain->last_link = newLink;
            }
            updateIndexes(chain->last_link);
            chain->chain_size++;
        }

        /// <summary>
        /// Добавить в указанную точку по индексу
        /// </summary>
        /// <param name="index"> индекс </param>
        /// <param name="value"> значение </param>
        void at(size_t index, TYPE value) {
            if (index == 0) {
                front(value);
                return;
            }
            if (index >= chain->getSize()) {
                back(value);
                return;
            }
            chain->seek(index);
            Link<TYPE>* newLink = new Link<TYPE>(value);
            Link<TYPE>* prev = chain->current_link->getPrev();
            newLink->setNext(chain->current_link);
            newLink->setPrev(prev);
            prev->setNext(newLink);
            chain->current_link->setPrev(newLink);
            updateIndexes(chain->current_link);
            chain->chain_size++;
        }

        /// <summary>
        /// Обновляет индексы у звеньев цепи
        /// </summary>
        /// <param name="startNode"> узел, от которого нужно начинать обновление</param>
        void updateIndexes(Link<TYPE>* startNode) {
            Link<TYPE>* current = startNode;
            size_t index = startNode->getIndex();
            while (current != nullptr) {
                current->setIndex(index++);
                current = current->getNext();
            }
        }

    };

    /// <summary>
    /// Удаление элементов
    /// </summary>
    class NodeDeleter {
    private:
        Chain2<TYPE>* chain;

    public:
        NodeDeleter(Chain2<TYPE>* chain) : chain(chain) {}

        /// <summary>
        /// Из начала
        /// </summary>
        void front() {
            if (chain->isEmpty()) {
                return;
            }
            Link<TYPE>* tmp = chain->first_link;
            chain->first_link = chain->first_link->getNext();
            if (chain->first_link != nullptr) {
                chain->first_link->setPrev(nullptr);
            }
            else {
                chain->last_link = nullptr;
            }
            delete tmp;
            chain->chain_size--;
        }

        /// <summary>
        /// Из конца
        /// </summary>
        void back() {
            if (chain->isEmpty()) {
                return;
            }
            Link<TYPE>* tmp = chain->last_link;
            chain->last_link = chain->last_link->getPrev();
            if (chain->last_link != nullptr) {
                chain->last_link->setNext(nullptr);
            }
            else {
                chain->first_link = nullptr;
            }
            delete tmp;
            chain->chain_size--;
        }

        /// <summary>
        /// Из указанной точки
        /// </summary>
        /// <param name="index"> индекс </param>
        void at(size_t index) {
            if (chain->isEmpty() || index >= chain->getSize()) {
                return;
            }
            chain->seek(index);
            Link<TYPE>* tmp = chain->current_link;
            if (chain->current_link == chain->first_link) {
                front();
            }
            else if (chain->current_link == chain->last_link) {
                back();
            }
            else {
                chain->current_link->getPrev()->setNext(chain->current_link->getNext());
                chain->current_link->getNext()->setPrev(chain->current_link->getPrev());
                delete tmp;
                chain->chain_size--;
            }
        }
    };


public:
    /// <summary>
    /// Инициализация пустого списка
    /// </summary>
    Chain2() {}

    /// <summary>
    /// Добавление элементов
    /// </summary>
    NodeAdder adder{ this };

    /// <summary>
    /// Удаление элементов
    /// </summary>
    NodeDeleter deleter{ this };

    /// <summary>
    /// Инициализация списка и добавление элемента
    /// </summary>
    /// <param name="value"> значение </param>
    Chain2(TYPE value) : chain_size(1) {
        current_link = new Link<TYPE>(value);
        first_link = current_link;
        last_link = current_link;
    }

    /// <summary>
    /// Деструктор
    /// </summary>
    ~Chain2() {
        clear();
    }

    /// <summary>
    /// Конструктор копирования
    /// </summary>
    /// <param name="other"></param>
    Chain2(const Chain2& other) : chain_size(other.chain_size), current_link(nullptr), first_link(nullptr), last_link(nullptr) {
        Link<TYPE>* other_current = other.first_link;
        while (other_current != nullptr) {
            adder.back(other_current->getData());
            other_current = other_current->getNext();
        }
    }

    /// <summary>
    /// Оператор копирования
    /// </summary>
    /// <param name="other"></param>
    /// <returns></returns>
    Chain2& operator=(const Chain2& other) {
        if (this != &other) {
            clear();
            chain_size = other.chain_size;
            Link<TYPE>* other_current = other.first_link;
            while (other_current != nullptr) {
                adder.back(other_current->getData());
                other_current = other_current->getNext();
            }
        }
        return *this;
    }

    /// <summary>
    /// Конструктор переноса
    /// </summary>
    /// <param name="other"></param>
    Chain2(Chain2&& other) noexcept : chain_size(other.chain_size), current_link(other.current_link), first_link(other.first_link), last_link(other.last_link) {
        other.chain_size = 0;
        other.current_link = nullptr;
        other.first_link = nullptr;
        other.last_link = nullptr;
    }

    /// <summary>
    /// Оператор переноса
    /// </summary>
    /// <param name="other"></param>
    /// <returns></returns>
    Chain2& operator=(Chain2&& other) noexcept {
        if (this != &other) {
            clear();
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

    /// <summary>
    /// Возвращает размер спписка
    /// </summary>
    /// <returns> размер </returns>
    size_t getSize() const /*override*/ { return chain_size; }

    /// <summary>
    /// Перейти к правому (следующему) звену
    /// </summary>
    void right() {
        if (current_link->getNext() != nullptr) {
            current_link = current_link->getNext();
        }
    }

    /// <summary>
    /// Перейти к левому (предыдущему) звену
    /// </summary>
    void left() {
        if (current_link->getPrev() != nullptr) {
            current_link = current_link->getPrev();
        }
    }

    /// <summary>
    /// Перейти по указанному индексу
    /// </summary>
    /// <param name="index"></param>
    void seek(size_t index)
    {
        bool mode = false;
        if (index >= chain_size && index < 0)
            if (index >= chain_size && index < 0)
                mode = true; else mode = false;
        while (index != current_link->getIndex())
            if (mode) right(); else left();
    }

    /// <summary>
    /// Перейти к началу
    /// </summary>
    void toStart() { current_link = first_link; }

    /// <summary>
    /// Перейти к концу
    /// </summary>
    void toEnd() { current_link = last_link; }

    /// <summary>
    /// Конвертация в вектор
    /// </summary>
    /// <returns></returns>
    std::vector<TYPE> toArray() {
        std::vector<TYPE> array;
        Link<TYPE>* ptr = first_link;
        while (ptr != nullptr) {
            array.push_back(ptr->getData());
            ptr = ptr->getNext();
        }
        return array;
    }

    /// <summary>
    /// Сортировка списка
    /// </summary>
    void sort() {
        if (chain_size <= 1) {
            return;
        }

        Link<TYPE>* current = first_link->getNext();
        while (current != nullptr) {
            Link<TYPE>* key = current;
            TYPE keyValue = key->getData();
            Link<TYPE>* prev = key->getPrev();

            while (prev != nullptr && prev->getData() > keyValue) {
                prev->getNext()->setData(prev->getData());
                prev = prev->getPrev();
            }

            if (prev == nullptr) {
                first_link->setData(keyValue);
            }
            else {
                prev->getNext()->setData(keyValue);
            }

            current = current->getNext();
        }
    }

    /// <summary>
    /// Поиск элемента в списке
    /// </summary>
    /// <param name="value"> значение элемента </param>
    /// <returns> указатель на звено с найденным элементом (на текущий, если не найдено) </returns>
    Link<TYPE>* search(TYPE value) {
        Link<TYPE>* ptr = first_link;
        while (ptr != nullptr) {
            if (ptr->getData() == value) {
                return ptr; // Возвращаем найденный элемент
            }
            ptr = ptr->getNext();
        }
        return current_link; // Возвращаем текущий элемент, если не найдено
    }


    /// <summary>
    /// Конкатенация списков
    /// </summary>
    /// <param name="other"> присоединяемый список </param>
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

    /// <summary>
    /// Разделение по индексу на два списка
    /// </summary>
    /// <param name="index"> разделяющий индекс </param>
    /// <param name="secondList"> список, принимающий отделённую часть первого списка</param>
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

    /// <summary>
    /// Очистка списка
    /// </summary>
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
    bool isEmpty() { if (chain_size == 0) return true; else return false; }

    /// <summary>
    /// Вывод списка через cout
    /// </summary>
    /// <param name="os"></param>
    /// <param name="chain"></param>
    /// <returns></returns>
    friend std::ostream& operator<<(std::ostream& os, const Chain2<TYPE>& chain) {
        Link<TYPE>* ptr = chain.first_link;
        while (ptr != nullptr) {
            os << ptr->getData();
            if (ptr->getNext() != nullptr) {
                os << ", ";
            }
            ptr = ptr->getNext();
        }
        return os;
    }
};

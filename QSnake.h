#pragma once
#include "Interface.h"

template<typename TYPE>
class QSnake : public CustomStack<TYPE> {
private:
    size_t queue_size = 0;
    Level<TYPE>* front = nullptr;
    Level<TYPE>* rear = nullptr;

public:
    QSnake() {}

    ~QSnake() {
        while (front != nullptr) {
            Level<TYPE>* tmp = front;
            front = front->getPrev();
            delete tmp;
        }
    }

    TYPE push() override {
        if (front == nullptr) {
            throw std::out_of_range("Queue is empty");
        }

        TYPE res = front->getData();
        remove();
        return res;
    }

    void pull(TYPE data) override {
        add(data);
    }

    size_t getSize() override { return queue_size; }

    std::string toString() override {
        std::string result;
        Level<TYPE>* current = front;
        while (current != nullptr) {
            result += std::to_string(current->getData()) + " ";
            current = current->getPrev();
        }
        return result;
    }

private:
    void add(TYPE data) {
        Level<TYPE>* next = new Level<TYPE>(data);
        if (front == nullptr) {
            front = next;
        }
        else {
            rear->setPrev(next);
        }
        rear = next;
        ++queue_size;
    }

    void remove() {
        if (front == nullptr) {
            return;
        }

        Level<TYPE>* tmp = front;
        front = front->getPrev();
        delete tmp;
        --queue_size;
        if (front == nullptr) {
            rear = nullptr;
        }
    }
};


#pragma once
#include "Chain2.h"

template<typename TYPE>
class QSnake
{
private:
    size_t queue_size = 0;
    Chain2<TYPE> queue;

public:
    /// <summary>
    /// ������������� ������ �������
    /// </summary>
    QSnake() {}
    
    /// ����������
    ~QSnake() {}

   /// ����������� ��������
    TYPE pull() {
        if (queue.getSize() == 0) {
            throw std::out_of_range("Queue is empty");
        }

        TYPE res = queue.getFirst()->getData();
        queue.deleter.front();
        return res;
    }

    /// ��������� �������� � �������
    void push(TYPE data) {
        queue.adder.back(data);
    }

    /// <summary>
    /// �������� ������ �������
    /// </summary>
    size_t getSize() { return queue.getSize(); }

    /// ������� ������� �������
    std::string toString() {
        std::vector<TYPE> elements = queue.toArray();
        std::stringstream ss;
        for (const auto& element : elements) {
            ss << element << " ";
        }
        return ss.str();
    }
};

#include <iostream>
#include "Chain2.h"
#include "HeavyIronWell.h"
#include "Ladder3One.h"
#include "QSnake.h"
#include <cassert>

using namespace std;

void testChain2() {
    // Тест создания списка с одним элементом
    Chain2<int> chain(5);
    assert(chain.getSize() == 1);
    assert(chain.getFirst()->getData() == 5);
    assert(chain.getLast()->getData() == 5);

    // Тест добавления элемента в начало
    chain.adder.front(3);
    assert(chain.getSize() == 2);
    assert(chain.getFirst()->getData() == 3); 
    // Тест добавления элемента в конец
    chain.adder.back(8);
    assert(chain.getSize() == 3);
    assert(chain.getLast()->getData() == 8);

    // Тест добавления элемента по индексу
    chain.adder.at(1, 6); 
    assert(chain.getSize() == 4);
    assert(chain.getFirst()->getNext()->getData() == 6);
    // Тест удаления элемента в начале
    chain.deleter.front();
    assert(chain.getSize() == 3);
    assert(chain.getFirst()->getData() == 6);

    // Тест удаления элемента в конце
    chain.deleter.back();
    assert(chain.getSize() == 2);
    assert(chain.getLast()->getData() == 5);

    // Тест удаления элемента по индексу
    chain.deleter.at(0);
    assert(chain.getSize() == 1);
    assert(chain.getFirst()->getData() == 5);

    chain.adder.front(1);
    // Тест перемещения к первому элементу
    chain.toStart();
    assert(chain.getCurrent() == chain.getFirst());

    // Тест перемещения к последнему элементу
    chain.toEnd();
    assert(chain.getCurrent() == chain.getLast());
    // Тест перемещения на один элемент вперед
    chain.right();
    assert(chain.getCurrent() == chain.getLast());
    // Тест перемещения на один элемент назад
    chain.left();
    assert(chain.getCurrent() == chain.getFirst());

    chain.adder.at(2, 6);
    // Тест поиска элемента в списке
    assert(chain.search(6)->getData() == 6);
    assert(chain.search(10)->getData() == chain.getCurrent()->getData());

    // Тест сортировки пустого списка
    Chain2<int> emptyChain;
    emptyChain.sort();
    assert(emptyChain.getSize() == 0);

    // Тест сортировки списка с одним элементом
    Chain2<int> singleChain(3);
    singleChain.sort();
    assert(singleChain.getSize() == 1);
    assert(singleChain.getFirst()->getData() == 3);

    // Тест сортировки списка с несколькими элементами
    Chain2<int> unsortedChain;
    unsortedChain.adder.back(9);
    unsortedChain.adder.back(2);
    unsortedChain.adder.back(7);
    unsortedChain.adder.back(4);
    unsortedChain.adder.back(1);
    unsortedChain.sort();
    assert(unsortedChain.getSize() == 5);
    assert(unsortedChain.getFirst()->getData() == 1);
    assert(unsortedChain.getLast()->getData() == 9);
    cout << unsortedChain << endl;
    // Тест конвертации списка в массив
    std::vector<int> array = unsortedChain.toArray();
    assert(array.size() == 5);
    assert(array[0] == 1);
    assert(array[4] == 9);

    // Тест разделения списка на два по индексу
    Chain2<int> secondChain;
    unsortedChain.divide(2, secondChain);
    assert(unsortedChain.getSize() == 2);
    assert(secondChain.getSize() == 3);
    assert(unsortedChain.getLast()->getData() == 4);
    assert(secondChain.getFirst()->getData() == 7);

    // Тест объединения двух списков
    unsortedChain.concatenate(secondChain);
    assert(unsortedChain.getSize() == 5);
    assert(secondChain.getSize() == 0);
    assert(unsortedChain.getLast()->getData() == 9);
}

void testHIWell() {
    // Создание объекта HIWell
    HIWell<int> well;

    // Проверка метода push
    well.push(5);
    assert(well.getSize() == 1);

    // Проверка метода pull
    int pulledValue = well.pull();
    assert(pulledValue == 5);
    assert(well.getSize() == 0);

    // Проверка метода getSize
    assert(well.getSize() == 0);

    // Проверка метода clear
    well.push(10);
    well.push(20);
    well.clear();
    assert(well.getSize() == 0);

    // Проверка метода peak
    assert(well.isEmpty());
    well.push(30);
    assert(well.peak() == 30);
    assert(well.getSize() == 1);

    // Проверка метода isEmpty
    assert(!well.isEmpty());
}

void testQSnake() {
    // Создание объекта QSnake
    QSnake<int> snake;

    // Проверка метода push на пустой очереди
    try {
        int poppedValue = snake.pull();
        // Если мы дошли до этой точки, значит ошибка - метод push должен выбросить исключение
        assert(false);
    }
    catch (const std::out_of_range& e) {
        // Ожидаемое исключение - всё в порядке
    }

    // Добавление элементов в очередь
    snake.push(5);
    snake.push(10);
    snake.push(15);

    // Проверка метода getSize
    assert(snake.getSize() == 3);

    // Проверка метода toString
    std::string str = snake.toString();
    assert(str == "5 10 15 ");

    // Проверка метода push после добавления элементов
    int poppedValue = snake.pull();
    assert(poppedValue == 5);
    assert(snake.getSize() == 2);

    // Проверка метода push после извлечения всех элементов
    poppedValue = snake.pull();
    assert(poppedValue == 10);
    assert(snake.getSize() == 1);

    poppedValue = snake.pull();
    assert(poppedValue == 15);
    assert(snake.getSize() == 0);

    // Попытка извлечения элемента из пустой очереди
    try {
        poppedValue = snake.pull();
        // Если мы дошли до этой точки, значит ошибка - метод push должен выбросить исключение
        assert(false);
    }
    catch (const std::out_of_range& e) {
        // Ожидаемое исключение - всё в порядке
    }
}

void testPostFix() {
    // Тест 1: Проверка корректного вычисления выражения "2 3 +"
    {
        Ladder3 xxx;
        xxx.setExpression("2 3 +");
        assert(xxx.postfix().calculate() == 5);
    }

    // Тест 2: Проверка вычисления выражения "-2 3 + 4 /"
    {
        Ladder3 yyy;
        yyy.setExpression("-2 3 + 4 /");
        assert(yyy.postfix().calculate() == 0.25);
    }

    // Тест 3: Проверка обработки неправильного выражения
    {
        Ladder3 zzz;
        zzz.setExpression("2 3 + *"); // Оператор * без достаточного количества операндов
        cout << zzz.postfix().calculate() << endl;
        //assert(zzz.postfix().calculate() == 5);
    }
}

void testRadixSort() {
    // Тест случая с пустым списком
    Chain2<int> emptyList;
    emptyList.radixSort();
    assert(emptyList.getSize() == 0);

    // Тест случая с одним элементом
    Chain2<int> singleElementList(42);
    singleElementList.radixSort();
    assert(singleElementList.getSize() == 1);
    assert(singleElementList.getFirst()->getData() == 42);

    // Тест случая, когда элементы уже отсортированы
    Chain2<int> sortedList;
    sortedList.adder.back(10);
    sortedList.adder.back(20);
    sortedList.adder.back(30);
    sortedList.adder.back(40);
    sortedList.adder.back(50);
    sortedList.radixSort();
    assert(sortedList.getSize() == 5);
    assert(sortedList.getFirst()->getData() == 10);
    assert(sortedList.getLast()->getData() == 50);

    // Тест случая, когда элементы в обратном порядке
    Chain2<int> reverseOrderList;
    reverseOrderList.adder.back(50);
    reverseOrderList.adder.back(40);
    reverseOrderList.adder.back(30);
    reverseOrderList.adder.back(20);
    reverseOrderList.adder.back(10);
    reverseOrderList.radixSort();
    assert(reverseOrderList.getSize() == 5);
    assert(reverseOrderList.getFirst()->getData() == 10);
    assert(reverseOrderList.getLast()->getData() == 50);

    // Тест случая с произвольным набором элементов
    Chain2<int> unsortedList;
    unsortedList.adder.back(170);
    unsortedList.adder.back(45);
    unsortedList.adder.back(75);
    unsortedList.adder.back(90);
    unsortedList.adder.back(2);
    unsortedList.adder.back(802);
    unsortedList.adder.back(24);
    unsortedList.adder.back(2);
    unsortedList.radixSort();
    assert(unsortedList.getSize() == 8);
    assert(unsortedList.getFirst()->getData() == 2);
    assert(unsortedList.getLast()->getData() == 802);
}

int main() {
    testChain2();
    testHIWell();
    testQSnake();
    testPostFix();
    testRadixSort();
    std::cout << "All tests passed successfully!" << std::endl;
    return 0;
}


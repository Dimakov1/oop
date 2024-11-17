#include <iostream>
#include <string>
#include <cassert>
#include <memory_resource>
#include "../include/CustomMemoryResource.hpp"
#include "../include/Stack.hpp"

struct Person {
    std::string name;
    int age;

    Person() : name(""), age(0) {}
    Person(const std::string& n, int a) : name(n), age(a) {}
};

void test_int_stack() {
    std::cout << "Тестирование стека с типом int..." << std::endl;

    CustomMemoryResource custom_resource;
    std::pmr::polymorphic_allocator<int> int_alloc(&custom_resource);

    Stack<int> int_stack(int_alloc);

    assert(int_stack.empty());
    std::cout << "Проверка пустого стека прошла успешно." << std::endl;

    for (int i = 1; i <= 5; ++i) {
        int_stack.push(i);
    }
    assert(int_stack.size() == 5);
    std::cout << "Добавление элементов прошло успешно." << std::endl;

    assert(int_stack.top() == 5);
    std::cout << "Проверка верхнего элемента прошла успешно." << std::endl;

    int_stack.pop();
    assert(int_stack.top() == 4);
    std::cout << "Удаление элемента прошло успешно." << std::endl;

    std::cout << "Итерация через Integer Stack: ";
    for (auto it = int_stack.begin(); it != int_stack.end(); ++it) {
        std::cout << *it << " ";
    }
    std::cout << std::endl;

    while (!int_stack.empty()) {
        int_stack.pop();
    }
    assert(int_stack.empty());
    std::cout << "Очистка стека прошла успешно." << std::endl;

    std::cout << "Тестирование стека с типом int прошло успешно.\n" << std::endl;
}

void test_person_stack() {
    std::cout << "Тестирование стека с типом Person..." << std::endl;

    CustomMemoryResource custom_resource;
    std::pmr::polymorphic_allocator<Person> person_alloc(&custom_resource);

    Stack<Person> person_stack(person_alloc);

    assert(person_stack.empty());
    std::cout << "Проверка пустого стека прошла успешно." << std::endl;

    person_stack.push(Person("Alice", 30));
    person_stack.push(Person("Bob", 25));
    person_stack.push(Person("Charlie", 35));
    assert(person_stack.size() == 3);
    std::cout << "Добавление элементов прошло успешно." << std::endl;

    assert(person_stack.top().name == "Charlie");
    assert(person_stack.top().age == 35);
    std::cout << "Проверка верхнего элемента прошла успешно." << std::endl;

    person_stack.pop();
    assert(person_stack.top().name == "Bob");
    assert(person_stack.top().age == 25);
    std::cout << "Удаление элемента прошло успешно." << std::endl;

    std::cout << "Итерация через Person Stack:" << std::endl;
    for (auto it = person_stack.begin(); it != person_stack.end(); ++it) {
        std::cout << "Name: " << it->name << ", Age: " << it->age << std::endl;
    }

    while (!person_stack.empty()) {
        person_stack.pop();
    }
    assert(person_stack.empty());
    std::cout << "Очистка стека прошла успешно." << std::endl;

    std::cout << "Тестирование стека с типом Person прошло успешно.\n" << std::endl;
}

void test_memory_reuse() {
    std::cout << "Тестирование повторного использования памяти..." << std::endl;

    CustomMemoryResource custom_resource;
    std::pmr::polymorphic_allocator<int> int_alloc(&custom_resource);

    {
        Stack<int> int_stack(int_alloc);
        for (int i = 0; i < 10; ++i) {
            int_stack.push(i);
        }
        for (int i = 0; i < 10; ++i) {
            int_stack.pop();
        }
    } 

    {
        Stack<int> int_stack(int_alloc);
        for (int i = 100; i < 110; ++i) {
            int_stack.push(i);
        }
        for (int i = 109; i >= 100; --i) {
            assert(int_stack.top() == i);
            std::cout << "Top элемента: " << int_stack.top() << " соответствует ожидаемому значению " << i << std::endl;
            int_stack.pop();
        }
    }

    std::cout << "Тестирование повторного использования памяти прошло успешно.\n" << std::endl;
}

void test_memory_cleanup() {
    std::cout << "Тестирование освобождения неосвобожденной памяти при разрушении memory_resource..." << std::endl;

    {
        CustomMemoryResource custom_resource;
        std::pmr::polymorphic_allocator<int> int_alloc(&custom_resource);

        Stack<int> int_stack(int_alloc);
        int_stack.push(1);
        int_stack.push(2);
    }

    std::cout << "Тестирование освобождения памяти при разрушении memory_resource прошло успешно.\n" << std::endl;
}

void test_exceptions() {
    std::cout << "Тестирование исключений при операциях на пустом стеке..." << std::endl;

    CustomMemoryResource custom_resource;
    std::pmr::polymorphic_allocator<int> int_alloc(&custom_resource);

    Stack<int> empty_stack(int_alloc);

    assert(empty_stack.empty());

    try {
        empty_stack.pop();
        assert(false);
    } catch (const std::out_of_range& e) {
        std::cout << "Поймано исключение при pop на пустом стеке: " << e.what() << std::endl;
    }

    try {
        empty_stack.top();
        assert(false);
    } catch (const std::out_of_range& e) {
        std::cout << "Поймано исключение при top на пустом стеке: " << e.what() << std::endl;
    }

    std::cout << "Тестирование исключений прошло успешно.\n" << std::endl;
}

int main() {
    std::cout << "Запуск тестов контейнера Stack...\n" << std::endl;

    test_int_stack();
    test_person_stack();
    test_memory_reuse();
    test_memory_cleanup();
    test_exceptions();

    std::cout << "Все тесты прошли успешно!" << std::endl;
    return 0;
}

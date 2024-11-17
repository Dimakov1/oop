#include <iostream>
#include <string>
#include <cassert>
#include "CustomMemoryResource.hpp"
#include "Stack.hpp"

struct Person {
    std::string name;
    int age;

    Person() : name(""), age(0) {}
    Person(const std::string& n, int a) : name(n), age(a) {}
};

int main() {
    CustomMemoryResource custom_resource;
    std::pmr::polymorphic_allocator<int> int_alloc(&custom_resource);
    std::pmr::polymorphic_allocator<Person> person_alloc(&custom_resource);

    Stack<int> int_stack(int_alloc);
    for (int i = 1; i <= 5; ++i) {
        int_stack.push(i);
    }

    assert(int_stack.size() == 5);
    std::cout << "Integer Stack Size: " << int_stack.size() << std::endl;

    assert(int_stack.top() == 5);
    std::cout << "Top of Integer Stack: " << int_stack.top() << std::endl;

    int_stack.pop();
    assert(int_stack.top() == 4);
    std::cout << "Top after pop: " << int_stack.top() << std::endl;

    std::cout << "Iterating through Integer Stack: ";
    for (auto it = int_stack.begin(); it != int_stack.end(); ++it) {
        std::cout << *it << " ";
    }
    std::cout << std::endl;

    Stack<Person> person_stack(person_alloc);
    person_stack.push(Person("Alice", 30));
    person_stack.push(Person("Bob", 25));
    person_stack.push(Person("Charlie", 35));

    assert(person_stack.size() == 3);
    std::cout << "Person Stack Size: " << person_stack.size() << std::endl;

    assert(person_stack.top().name == "Charlie");
    std::cout << "Top of Person Stack: " << person_stack.top().name << ", " << person_stack.top().age << std::endl;

    person_stack.pop();
    assert(person_stack.top().name == "Bob");
    std::cout << "Top after pop: " << person_stack.top().name << ", " << person_stack.top().age << std::endl;

    std::cout << "Iterating through Person Stack:" << std::endl;
    for (auto it = person_stack.begin(); it != person_stack.end(); ++it) {
        std::cout << "Name: " << it->name << ", Age: " << it->age << std::endl;
    }

    Stack<int> empty_stack(int_alloc);
    assert(empty_stack.empty());
    std::cout << "Empty stack is empty: " << std::boolalpha << empty_stack.empty() << std::endl;

    try {
        empty_stack.pop();
    } catch (const std::out_of_range& e) {
        std::cout << "Caught exception on pop from empty stack: " << e.what() << std::endl;
    }

    try {
        empty_stack.top();
    } catch (const std::out_of_range& e) {
        std::cout << "Caught exception on top from empty stack: " << e.what() << std::endl;
    }

    std::cout << "All tests passed successfully!" << std::endl;
    return 0;
}

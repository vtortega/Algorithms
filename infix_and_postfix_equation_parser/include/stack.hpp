#ifndef STACK_HPP
#define STACK_HPP
#include <iostream>

template <typename T>
class Stack {
    public:
     Stack();
     ~Stack();
     void push(T value);
     T pop();
     T peek() const;
     bool empty() const;
     int size() const;
    private:
     struct NodeStack { 
         T data;
         NodeStack* next;
     };
     NodeStack* top;
     int m_size;
    };

template <typename T>
Stack<T>::Stack()
    : top(nullptr), m_size(0)
{
}

template <typename T>
Stack<T>::~Stack()
{
    while (!empty()) {
        pop();
    }
}

template <typename T>
void Stack<T>::push(T value)
{
    NodeStack* newNode = new NodeStack{value, top};
    top = newNode;
    m_size++;
}

template <typename T>
T Stack<T>::pop()
{
    if (empty()) {
        throw std::runtime_error(" Stack vazio");
    }
    NodeStack* nodeToDelete = top;
    T value = top->data;
    top = top->next;
    delete nodeToDelete;
    m_size--;
    return value;
}

template <typename T>
T Stack<T>::peek() const
{
    if (empty()) {
        throw std::runtime_error(" Stack vazio");
    }
    return top->data;
}

template <typename T>
bool Stack<T>::empty() const
{
    return (top == nullptr);
}

template <typename T>
int Stack<T>::size() const
{
    return m_size;
}
#endif 

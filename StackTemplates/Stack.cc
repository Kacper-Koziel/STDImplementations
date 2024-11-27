#pragma once

#include "Stack.h"

#include <cstring>
#include <exception>
#include <iostream>

template <typename T>
Stack<T>::Stack()
{
    this->stack = new T[8];
    this->size = 0;
    this->capacity = 8;
}

template <typename T>
Stack<T>::Stack(size_t capacity)
{
    this->capacity = capacity;
    this->size = 0;
    this->stack = new T[capacity];
}

template <typename T>
Stack<T>::Stack(const Stack<T> &other)
{
    if (this == &other)
    {
        return;
    }

    this->capacity = other.getCapacity();
    this->size = other.getSize();

    this->stack = new T[other.getCapacity()];

    std::copy(other.get(), other.get() + other.getSize(), this->stack);
}

template <typename T>
Stack<T>::Stack(Stack<T> &&other) : stack(other.stack), size(other.size), capacity(other.capacity)
{
    other.stack = nullptr;
    other.capacity = 0;
    other.size = 0;
}

template <typename T>
Stack<T>::~Stack()
{
    delete[] this->stack;
    this->stack = nullptr;
}

template <typename T>
Stack<T> &Stack<T>::operator=(const Stack<T> &other)
{
    if (this == &other)
    {
        return *this;
    }

    Stack<T> backup(*this);

    this->size = other.getSize();
    this->capacity = other.getCapacity();
    this->stack = new T[other.getCapacity()];

    try
    {
        std::copy(other.get(), other.get() + other.getSize(), this->stack); 
    }
    catch(const std::bad_alloc& e)
    {
        *this = backup;
        throw;
    }

    return *this;
}

template <typename T>
Stack<T> &Stack<T>::operator=(Stack<T> &&other)
{
    if (this == &other)
    {
        return *this;
    }

    delete[] this->stack;

    this->stack = other.stack;
    this->size = other.size;
    this->capacity = other.capacity;

    other.stack = nullptr;
    other.size = 0;
    other.capacity = 0;
    
    return *this;
}

template <typename T>
void Stack<T>::reserve(size_t newCapacity)
{
    if (newCapacity <= this->size)
    {
        throw std::invalid_argument("new size smaller than size, Possible data lose");
    }

    if (newCapacity <= capacity)
    {
        return;
    }
    
    T* temp = new T[newCapacity];

    std::copy(this->stack, this->stack + this->size, temp);

    delete[] this->stack;

    this->stack = temp;
    this->capacity = newCapacity; 
}

template <typename T>
void Stack<T>::push(const T &value)
{
    if (this->size >= this->capacity)
    {
        reserve(this->capacity * 2);
    }
    
    *(this->stack + this->size) = value;
    this->size++;
}

template <typename T>
const T &Stack<T>::top() const
{
    if (this->size == 0)
    {
        throw std::out_of_range("Stack is empty");
    }

    return *(this->stack + this->size - 1);
}

template <typename T>
void Stack<T>::pop()
{
    if (this->size == 0)
    {
        throw std::out_of_range("Stack is empty");
    }

    this->size--;
}

template <typename T>
bool Stack<T>::empty() const
{
    return this->size == 0;
}

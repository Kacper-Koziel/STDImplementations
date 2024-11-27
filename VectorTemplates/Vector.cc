#pragma once

#include "Vector.h"

#include <cstring>
#include <exception>
#include <iostream>

template <typename T>
Vector<T>& Vector<T>::operator=(const Vector<T> &other)
{
    if (this == &other)
    {
        return *this;
    }

    Vector<T> backup(*this);

    delete[] this->vector;

    this->size = other.getSize();
    this->capacity = other.getCapacity();
    this->vector = new T[other.getCapacity()];

    try
    {
        std::copy(other.get(), other.get() + other.getSize(), this->vector);
    }
    catch(const std::bad_alloc& e)
    {
        *this = backup;
        throw;
    }
    
    return *this;
}

template <typename T>
Vector<T> &Vector<T>::operator=(Vector<T> &&other) noexcept
{
    if (this == &other)
    {
        return *this;
    }
    
    delete[] this->vector;

    this->size = other.size;
    this->capacity = other.capacity;
    this->vector = other.vector;

    other.vector = nullptr;
    other.size = 0;
    other.capacity = 0;

    return *this;
}

template <typename T>
T &Vector<T>::operator[](unsigned int index)
{
    return *(this->vector + index);
}

template <typename T>
Vector<T>::Vector()
{
    this->vector = new T[16];
    this->size = 0;
    this->capacity = 16;   
}

template <typename T>
Vector<T>::Vector(size_t capacity)
{
    if (capacity < 1)
    {
        throw std::invalid_argument("Capacity cant be smaller than 1");
    }
    
    this->vector = new T[capacity];
    this->size = capacity;
    this->capacity = capacity;
}

template <typename T>
Vector<T>::Vector(size_t size, const T &fillValue)
{
    if (size < 1)
    {
        throw std::invalid_argument("Size cant be smaller than 1");
    }
    
    this->vector = new T[size];
    this->size = size;
    this->capacity = size;

    for (auto& i : *this)
    {
        i = fillValue;
    }
}

template <typename T>
Vector<T>::Vector(const Vector<T> &other)
{
    if (this == &other)
    {
        return;
    }

    this->size = other.getSize();
    this->capacity = other.getCapacity();
    this->vector = new T[other.getCapacity()];

    try
    {
        std::copy(other.get(), other.get() + other.getSize(), this->vector);
    }
    catch(const std::bad_alloc& e)
    {
        delete[] this->vector;
        throw;
    }
}

template <typename T>
Vector<T>::Vector(Vector<T> &&other) noexcept : vector(other.vector), size(other.size), capacity(other.capacity)
{
    other.vector = nullptr;
    other.size = 0;
    other.capacity = 0;
}

template <typename T>
Vector<T>::~Vector()
{
    delete[] this->vector;

    this->vector = nullptr;
}


template <typename T>
bool Vector<T>::empty() const
{
    return this->size == 0;
}

template <typename T>
void Vector<T>::reserve(size_t capacity)
{
    if (capacity < this->size)
    {
        throw std::invalid_argument("New capacity is smaller than size. Possible data loss");
    }

    if (capacity == this->capacity) return;

    T* newVect = new T[capacity];

    std::copy(this->vector, this->vector + this->size, newVect);

    delete[] this->vector;

    this->vector = newVect;
    this->capacity = capacity;
}

template <typename T>
void Vector<T>::resize(size_t newSize)
{
    if (newSize < this->size)
    {
        throw std::invalid_argument("New size is smaller than size. Possible data loss");
    }
    
    if (newSize <= this->capacity)
    {
        this->size = newSize;
        return;
    }
    
    T* newVector = new T[newSize];

    std::copy(this->vector, this->vector + this->size, newVector);

    delete[] this->vector;

    this->vector = newVector;
    this->capacity = newSize;
    this->size = newSize;
}

template <typename T>
void Vector<T>::push_back(T& value) 
{
    if (this->capacity <= this->size)
    {
        reserve(this->capacity * 2);
    }

    *(this->vector + this->size) = value;
    this->size++;
}

template <typename T>
void Vector<T>::clear()
{
    this->size = 0;
}

template <typename T>
void Vector<T>::resize(size_t newSize, const T &fillValue)
{
    if (newSize < 1)
    {
        throw std::invalid_argument("new size cant be smaller than 1");
    }

    if (this->size > newSize)
    {
        throw std::invalid_argument("Possible data lose, new size smaller than old size");
    }
    
    
    T* temp = new T[newSize];

    std::copy(this->vector, this->vector + this->size, temp);

    delete[] this->vector;

    this->capacity = newSize;
    this->vector = temp;
    
    for (size_t i = this->size; i < newSize; i++)
    {
        *(this->vector + i) = fillValue;
    }
    
    this->size = newSize;
}

template <typename T>
inline void Vector<T>::push_back(T &&value)
{
    if (this->capacity <= this->size)
    {
        reserve(this->capacity * 2);
    }

    *(this->vector + this->size) = std::move(value);
    this->size++;
}

template <typename T>
void Vector<T>::fill(const T &value)
{
    for (auto& i : *this)
    {
        i = value;
    }
}

template <typename T>
void Vector<T>::pop_back()
{
    if (empty())
    {
        throw std::out_of_range("Vector is empty");
    }

    this->size--;
}

template <typename T>
void Vector<T>::shrink_to_fit()
{
    if (this->size == this->capacity || this->size == 0) return;

    T* newVect = new T[this->size];

    std::copy(this->vector, this->vector + this->size, newVect);

    delete[] this->vector;

    this->vector = newVect;
    this->capacity = this->size;
}

template <typename T>
T &Vector<T>::at(unsigned int index)
{
    if (index >= this->size)
    {
        throw std::out_of_range("Index: " + std::to_string(index) + ". Vector max index: " + std::to_string(this->size - 1));
    }
    
    return *(this->vector + index);
}

template <typename T>
const T &Vector<T>::c_at(unsigned int index) const
{
    if (index >= this->size)
    {
        throw std::out_of_range("Index: " + std::to_string(index) + ". Vector max index: " + std::to_string(this->size - 1));
    }
    
    return *(this->vector + index);
}

template <typename T>
T &Vector<T>::front()
{
    if (this->size == 0)
    {
        throw std::out_of_range("Vector is empty");
    }
    

    return *(this->vector);
}

template <typename T>
T &Vector<T>::back()
{
    if (this->size == 0)
    {
        throw std::out_of_range("Vector is empty");
    }

    return *(this->vector + this->size - 1);
}

template <typename T>
T *Vector<T>::begin()
{
    return this->vector;
}

template <typename T>
T *Vector<T>::end()
{
    return this->vector + this->size;
}

template <typename T>
const T *Vector<T>::begin() const
{
    return this->vector;
}

template <typename T>
const T *Vector<T>::end() const
{
    return this->vector + this->size;
}

template <typename T>
void Vector<T>::insert(unsigned int index, const T &value)
{
    if (index > this->size)
    {
        throw std::out_of_range("Index bigger than size");
    }

    if (this->size >= this->capacity)
    {
        reserve(this->capacity * 2);
    }

    for (size_t i = this->size; i > index; i--)
    {
        *(this->vector + i) = *(this->vector + i - 1);
    }
    
    *(this->vector + index) = value;
    this->size++;
}

template <typename T>
void Vector<T>::erase(unsigned int index)
{
    if (index >= this->size)
    {
        throw std::out_of_range("Index bigger than size");
    }
    
    for (size_t i = index; i < this->size - 1; i++)
    {
        *(this->vector + i) = *(this->vector + i + 1);
    }

    this->size--;
}

template <typename T>
void Vector<T>::erase(unsigned int start, unsigned int end)
{ 
    if (start > end)
    {
        throw std::invalid_argument("Start cant be bigger than end");
    }
    
    if (start == end)
    {
        erase(start);
        return;
    }

    if (end >= this->size || end < 0)
    {
        throw std::invalid_argument("You cant erase non existed position");
    }

    for (size_t i = start; i < this->size - 1; i++)
    {
        *(this->vector + i) = *(this->vector + i + (end - start + 1));
    }
    
    this->size = this->size - (end - start + 1);
    
}

template <typename T>
void Vector<T>::display()
{
    std::cout << "Size: " << this->size << ", Capacity: " << this->capacity << std::endl;
    std::cout << std::endl;

    for(int i = 0; i < this->size; i++)
    {
        std::cout << "i: " << i << ", val: " << *(this->vector + i) << std::endl;
    }
}

template <typename T>
int Vector<T>::partition(int firstIndex, int lastIndex)
{
    T privot = *(this->vector + lastIndex);
    int i = firstIndex  - 1;

    for (int j = firstIndex; j < lastIndex; j++)
    {
        if(*(this->vector + j) <= privot)
        {
            ++i;
            std::swap(*(this->vector + i), *(this->vector + j));
        }
    }
    
    std::swap(*(this->vector + i + 1), *(this->vector + lastIndex));
    return i + 1;
}

template <typename T>
void Vector<T>::sort(int firstIndex, int lastIndex) // last index prob. size - 1;
{
    if (firstIndex < lastIndex)
    {
        int point = partition(firstIndex, lastIndex);

        sort(firstIndex, point - 1);
        sort(point + 1, lastIndex);
    }
    
}

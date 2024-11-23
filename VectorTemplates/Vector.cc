#pragma once

#include "Vector.h"

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
Vector<T> &Vector<T>::operator=(Vector<T> &&other)
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
        this->capacity = newSize;
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
        resize(this->capacity * 2);
    }

    *(this->vector + this->size) = value;
    this->size++;
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
Vector<T>::Vector()
{
    this->vector = new T[1];
    this->size = 0;
    this->capacity = 1;   
}

template <typename T>
Vector<T>::Vector(size_t capacity)
{
    if (capacity < 1)
    {
        throw std::invalid_argument("Capacity cant be smaller than 1");
    }
    
    this->vector = new T[capacity];
    this->size = 0;
    this->capacity = capacity;
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
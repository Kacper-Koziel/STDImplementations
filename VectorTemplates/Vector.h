#ifndef VECTOR_H
#define VECTOR_H
    #include <cstring>
    #include <exception>
    #include <iostream>

    template <typename T>
    class Vector
    {
    private:
        T* vector;
        size_t size;
        size_t capacity;
    public:
        Vector();
        Vector(size_t capacity);
        Vector(size_t size, const T& fillValue);
        Vector(const Vector<T>& other);
        Vector(Vector<T>&& other) noexcept;
        ~Vector();

        Vector<T>& operator=(const Vector<T>& other);
        Vector<T>& operator=(Vector<T>&& other);
        T& operator[](unsigned int index);

        const T* get() const { return this->vector; }
        const size_t getSize() const { return this->size; }
        const size_t getCapacity() const { return this->capacity; }

        bool empty() const;
        void clear();
        
        void reserve(size_t capacity);
        void resize(size_t newSize);
        void resize(size_t newSize, const T& fillValue);
        
        void push_back(T& value);
        void push_back(T&& value);
        
        void fill(const T& value);

        void pop_back();
        void shrink_to_fit();

        T& at(unsigned int index);
        const T& c_at(unsigned int index) const;
        T& front();
        T& back();
        
        T* begin();
        T* end();
        const T* begin() const;
        const T* end() const;

        void display();

        int partition(int firstIndex, int lastIndex);
        void sort(int firstIndex, int lastIndex);

        void insert(unsigned int index, const T& value);
        void erase(unsigned int index);
        void erase(unsigned int start, unsigned int end);
    };
    
#endif

#ifndef STACK_H
#define STACK_H
    
    #include <iostream>

    template <typename T>

    class Stack
    {
    private:
        T* stack;
        size_t size;
        size_t capacity;
    public:
        Stack();
        Stack(size_t capacity);
        Stack(const Stack<T>& other);
        Stack(Stack<T>&& other) noexcept;
        ~Stack();

        Stack<T>& operator=(const Stack<T>& other);
        Stack<T>& operator=(Stack<T>&& other) noexcept;

        void reserve(size_t newSize);
        void push(const T& value);
        const T& top() const;
        void pop();

        bool empty() const;

        const T* get() const { return this->stack; }
        const size_t getSize() const { return this->size; }
        const size_t getCapacity() const { return this->capacity; }
    };
    
#endif

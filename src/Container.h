#ifndef CONTAINER_H
#define CONTAINER_H

#include <string>
#include <iostream>

int const DEFAULT_CAPACITY = 10;
int const CAPACITY_MUL = 2;

template <class T>
class Container {
    public:
        Container(int initCapacity = DEFAULT_CAPACITY): m_size(0), m_capacity(initCapacity) {
            m_array = reinterpret_cast<T*>(operator new(sizeof(T) * initCapacity));
        }

        Container(const Container & other);
        Container & operator=(Container const & other);
        bool operator==(Container const & other);
        void pushBack(T const & value);
        T getByIndex(int index) const;
        void popBack();
        void clean();
        
        int getSize() const {
            return m_size;
        }

        bool isEmpty() const {
            return m_size == 0;
        }

        ~Container() {
            clean();
        }
    private:
        T* m_array;
        int m_size;
        int m_capacity;

        void reallocateMemory();
        void initThis(Container<T> const & other);
};

template <class T>
Container<T>::Container(Container<T> const & other) {
    initThis(other);
}

template <class T>
Container<T> & Container<T>::operator=(Container<T> const & other) {
    if (*this == other) {
        return *this;
    }

    initThis(other);

    return *this;
}

template <class T>
bool Container<T>::operator==(Container<T> const & other) {
    bool result = m_capacity == other.m_capacity && m_size == other.m_size;
    if(!result) {
        return false;
    }

    for(int i = 0; i < m_size; i++) {
        result = m_array[i] == other.m_array[i];
        if(!result) {
            return false;
        }
    }

    return true;
}

template <class T>
void Container<T>::pushBack(T const & value) {    
    if(m_size >= m_capacity) {
        reallocateMemory();
    }
    new (m_array + m_size++) T(value);
}

template <class T>
T Container<T>::getByIndex(int index) const {
    if(index < 0 || index >= m_size) {
        throw std::runtime_error("Index out of bounds exception:");
    }
    if(isEmpty()) {
        throw std::runtime_error("Container is empty exception");
    }
    return m_array[index];
}

template <class T>
void Container<T>::popBack() {
    m_array[--m_size].~T();
}

template <class T>
void Container<T>::clean() {
    for (int i = 0; i < m_size; i++) {
        m_array[i].~T();
    }
    operator delete(m_array);
}

template <class T>
void Container<T>::reallocateMemory() {
    m_capacity *= CAPACITY_MUL;
    T * newArray = reinterpret_cast<T*>(operator new(sizeof(T) * m_capacity));
    for(int i = 0; i < m_size; i++) {
        new (newArray + i) T(m_array[i]);
        m_array[i].~T();
    }

    operator delete(m_array);
    m_array = newArray;
}

template <class T>
void Container<T>::initThis(Container<T> const & other) {
    m_size = other.m_size;
    m_capacity = other.m_capacity;
    m_array = reinterpret_cast<T*>(operator new(sizeof(T) * m_capacity));
    for(int i = 0; i < m_size; i++) {
        new (m_array + i) T(other.m_array[i]);   
    }
}

#endif
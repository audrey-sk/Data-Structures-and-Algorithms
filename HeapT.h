


#pragma once
#include <stdexcept>
#include <algorithm>
#include <iostream>
#include <vector> 

template<typename T>
class HeapT {
private:
    T* array;             // Array for heap elements
    int capacity;         
    int currentSize;      // Current number of elements 

    // Helper functions to heapify 
    void heapifyUp(int index);
    void heapifyDown(int index);

public:
    // Constructor
    HeapT(int cap);

    // Copy constructor
    HeapT(const HeapT& other);

    // Destructor
    ~HeapT();

    // Assignment operator
    HeapT& operator=(const HeapT& other);

    // Insert
    void insert(const T& value);

    // Remove and return the root element
    T remove();

    // Peek - Returns the root element without removing it
    T peek() const;

    // Merge the current heap with another heap 
    HeapT merge(const HeapT& other) const;

    // Returns the size of the heap
    int size() const { return currentSize; }
};

// Constructor
template<typename T>
HeapT<T>::HeapT(int cap) : capacity(cap), currentSize(0) { 
    array = new T[capacity];
}

// Copy Constructor
template<typename T>
HeapT<T>::HeapT(const HeapT& other) : capacity(other.capacity), currentSize(other.currentSize) {
    array = new T[capacity];
    for (int i = 0; i < currentSize; ++i) {
        array[i] = other.array[i];
    }
}

// Destructor
template<typename T>
HeapT<T>::~HeapT() {
    delete[] array;
}

// Assignment Operator
template<typename T>
HeapT<T>& HeapT<T>::operator=(const HeapT& other) {
    if (this == &other) return *this; // Self-assignment c

    delete[] array; // Free existing memory

    capacity = other.capacity;
    currentSize = other.currentSize;
    array = new T[capacity];
    for (int i = 0; i < currentSize; ++i) {
        array[i] = other.array[i];
    }
    return *this;
}

// Insert Method
template<typename T>
void HeapT<T>::insert(const T& value) {
    if (currentSize == capacity) {
        throw std::runtime_error("Heap is full");
    }
    array[currentSize] = value;
    heapifyUp(currentSize);
    ++currentSize;
}

// Remove Method
template<typename T>
T HeapT<T>::remove() {
    if (currentSize == 0) {
        throw std::runtime_error("Heap is empty");
    }
    T root = array[0];
    array[0] = array[--currentSize];
    heapifyDown(0);
    return root;
}

// Peek Method
template<typename T>
T HeapT<T>::peek() const {
    if (currentSize == 0) {
        throw std::runtime_error("Heap is empty");
    }
    return array[0];
}

// HeapifyUp Helper Method
template<typename T>
void HeapT<T>::heapifyUp(int index) {
    while (index > 0) {
        int parent = (index - 1) / 2;
        if (array[index] >= array[parent]) break;
        std::swap(array[index], array[parent]);
        index = parent;
    }
}

// HeapifyDown Helper function
template<typename T>
void HeapT<T>::heapifyDown(int index) {
    while (index < currentSize) {
        int left = 2 * index + 1;
        int right = 2 * index + 2;
        int smallest = index;

        if (left < currentSize && array[left] < array[smallest]) {
            smallest = left;
        }
        if (right < currentSize && array[right] < array[smallest]) {
            smallest = right;
        }
        if (smallest == index) break;

        std::swap(array[index], array[smallest]);
        index = smallest;
    }
}

// Merge 
template<typename T>
HeapT<T> HeapT<T>::merge(const HeapT& other) const {
    HeapT<T> result(capacity + other.capacity);
    for (int i = 0; i < currentSize; ++i) {
        result.insert(array[i]);
    }
    for (int i = 0; i < other.currentSize; ++i) {
        result.insert(other.array[i]);
    }
    return result;
}
 
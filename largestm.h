

#pragma once
#include "HeapT.h"  // Include your HeapT class file
#include <vector>
#include <stdexcept>
#include <iostream> 

template <typename T>
std::vector<T> largestm(const std::vector<T>& v, int m) {
    std::vector<T> result;
    
    if (v.empty()) return result;  // Return empty result if empty

    // If the input vector size is less than or equal to m, return vector in descending order
    if (v.size() <= m) {
        HeapT<T> tempHeap(v.size());
        for (const T& value : v) {
            tempHeap.insert(value);
        }
        //get descending order
        while (tempHeap.size() > 0) {
            result.insert(result.begin(), tempHeap.remove());
        }
        return result;
    }

    //  min-heap with capacity m 
    HeapT<T> minHeap(m);

    // Insert elements into the min-heap 
    for (const T& value : v) {
        if (minHeap.size() < m) {
            minHeap.insert(value);
        } 
        else if (value > minHeap.peek()) {
            minHeap.remove();  // Remove the smallest in the heap
            minHeap.insert(value);  // Insert new element
        }
    }

    // Transfer elements from min-heap to result in reverse 
    while (minHeap.size() > 0) {
        result.insert(result.begin(), minHeap.remove());
    }

    return result;
}

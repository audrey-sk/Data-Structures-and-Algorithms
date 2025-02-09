#include "HeapT.h"      // Include HeapT class
#include "largestm.h"   // Include largestm function


using std::cout;
using std::endl;
using std::vector;
using std::runtime_error;

void testConstructor() {
    try {
        HeapT<int> heap(5);
        cout << "Constructor Test: Pass" << endl;
    } catch (...) {
        cout << "Constructor Test: Fail" << endl;
    }
}

void testCopyConstructor() {
    try {
        HeapT<int> heap1(5);
        heap1.insert(10);
        heap1.insert(20);
        HeapT<int> heap2(heap1);
        cout << "Copy Constructor Test: " << ((heap2.peek() == 10) ? "Pass" : "Fail") << endl;
    } catch (...) {
        cout << "Copy Constructor Test: Fail" << endl;
    }
}

void testAssignmentOperator() {
    try {
        HeapT<int> heap1(5);
        heap1.insert(5);
        heap1.insert(15);
        HeapT<int> heap2(5);
        heap2 = heap1;
        cout << "Assignment Operator Test: " << ((heap2.peek() == 5) ? "Pass" : "Fail") << endl;
    } catch (...) {
        cout << "Assignment Operator Test: Fail" << endl;
    }
}

void testInsert() {
    try {
        HeapT<int> heap(3);
        heap.insert(30);
        heap.insert(10);
        heap.insert(20);
        cout << "Insert Test: " << ((heap.peek() == 10) ? "Pass" : "Fail") << endl;
    } catch (...) {
        cout << "Insert Test: Fail" << endl;
    }
}

void testRemove() {
    try {
        HeapT<int> heap(3);
        heap.insert(15);
        heap.insert(5);
        heap.insert(10);
        int removed = heap.remove();
        cout << "Remove Test: " << ((removed == 5) ? "Pass" : "Fail") << endl;
    } catch (...) {
        cout << "Remove Test: Fail" << endl;
    }
}

void testPeek() {
    try {
        HeapT<int> heap(2);
        heap.insert(25);
        int peeked = heap.peek();
        cout << "Peek Test: " << ((peeked == 25) ? "Pass" : "Fail") << endl;
    } catch (...) {
        cout << "Peek Test: Fail" << endl;
    }
}

void testMerge() {
    try {
        HeapT<int> heap1(3);
        heap1.insert(10);
        heap1.insert(20);

        HeapT<int> heap2(3);
        heap2.insert(15);
        heap2.insert(25);

        HeapT<int> mergedHeap = heap1.merge(heap2);
        cout << "Merge Test: " << ((mergedHeap.size() == 4 && mergedHeap.peek() == 10) ? "Pass" : "Fail") << endl;
    } catch (...) {
        cout << "Merge Test: Fail" << endl;
    }
}

void testSize() {
    try {
        HeapT<int> heap(3);
        heap.insert(5);
        heap.insert(15);
        cout << "Size Test: " << ((heap.size() == 2) ? "Pass" : "Fail") << endl;
    } catch (...) {
        cout << "Size Test: Fail" << endl;
    }
}

void testDestructor() {
    // Destructor can't be tested directly, but if the program does not crash
    // when objects go out of scope, we assume it's implemented correctly.
    try {
        {
            HeapT<int> heap(2);
            heap.insert(1);
            heap.insert(2);
        }
        cout << "Destructor Test: Pass" << endl;
    } catch (...) {
        cout << "Destructor Test: Fail" << endl;
    }
}

int main() {
    testConstructor();
    testCopyConstructor();
    testAssignmentOperator();
    testInsert();
    testRemove();
    testPeek();
    testMerge();
    testSize();
    testDestructor();
    return 0;
}

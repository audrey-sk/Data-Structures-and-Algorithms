#include "StringList.h"
#include <stdexcept>
#include <iostream>
using std::out_of_range;
using std::cout;
using std::endl;

// Default constructor - makes an empty list of capacity 10
StringList::StringList()
{
	capacity = 10;
	n = 0;
	arr = new string[capacity];
}

// Copy constructor
StringList::StringList(const StringList& other)
{
	copyList(other);
}

// ***UNDOABLE
// Overloaded assignment operator
StringList& StringList::operator=(const StringList& other)
{
	if(&other != this)
	{
		history.pushHistory(createMemento());
		delete[] arr;
		copyList(other);
	}
	return *this;
}

// Destructor
StringList::~StringList()
{
	delete[] arr;
}

// ACCESSORS
// Returns the number of elements in the list
int StringList::size() const
{
	return n;
}

// Returns true if the list is empty, false otherwise
bool StringList::empty() const
{
	return n == 0;
}

// Returns the string at the given index
string StringList::get(int i) const
{
	checkBounds(i, "get");
	return arr[i];
}

// Returns the index of the first occurrence of the given string
int StringList::index(string s) const
{
	int i = 0;
	while (i < n && s != arr[i]) {
		i++;
	}
	if (i == n) {
		return -1;
	}
	else {
		return i;
	}
}

// Returns true iff the given string is in the list
bool StringList::contains(string str) const
{
	return !(index(str) == -1);
}

// Returns true if the two lists are equal, false otherwise.
// Does *not* consider any undo information when comparing two Stringlists. All
// that matters is that they have the same strings in the same order.
bool StringList::operator==(const StringList& sl) const
{
	if (size() != sl.size())
	{
		return false;
	}
	for (int i = 0; i < size(); i++)
	{
		if (get(i) != sl.get(i))
		{
			return false;
		}
	}
	return true;
}

// Returns true if the two lists are not equal, false otherwise
bool StringList::operator!=(const StringList& sl) const
{
	return !(*this == sl);
}

// Returns a string representation of the list.
string StringList::toString() const
{
	string result = "{";
	for (int i = 0; i < size(); i++)
	{
		if (i > 0) {
			result += ", ";
		}
		result += "\"" + get(i) + "\"";
	}
	return result + "}";
}

// MUTATORS

// ***UNDOABLE
// Sets the value at the given index
void StringList::set(int i, string str)
{
	checkBounds(i, "set");
	history.pushHistory(createMemento()); //create new object in the class 
	arr[i] = str;
}

// ***UNDOABLE
// Inserts the given string *before* the given index
void StringList::insertBefore(int pos, string str)
{
	// Doesn't use checkBounds because it's okay to insert at the end
	if (pos < 0 || pos > size()) {
		throw out_of_range("StringList::insertBefore index out of bounds");
	}
	checkCapacity();
	history.pushHistory(createMemento());  //create new object in the class 
	for (int i = n; i > pos; i--) {
		arr[i] = arr[i-1];
	}
	arr[pos] = str;
	n++;
}

// ***UNDOABLE
// Inserts the given string at the front of the list
void StringList::insertFront(string str)
{
	checkCapacity();
	insertBefore(0, str); //this already creates the object for us so no need for an extra push method here 
}

// ***UNDOABLE
// Inserts the given string at the back of the list
void StringList::insertBack(string str)
{
	checkCapacity();
	insertBefore(n, str); //this already creates the object for us so no need for an extra push method here
}

// ***UNDOABLE
// Removes the element at the given index and moves elements after it down
void StringList::remove(int pos)
{
	checkBounds(pos, "remove");
	history.pushHistory(createMemento()); //create new object in the class 
	for (int i = pos; i < n; i++) {
		arr[i] = arr[i + 1];
	}
	n--;
}

// ***UNDOABLE
// Empties the list
void StringList::removeAll()
{
	history.pushHistory(createMemento()); //create new object in the class 
	for (int i = 0; i < n; i++) {
		arr[i] = "";
	}
	n = 0;
}

// Undoes the last operation that modified the list
void StringList::undo()
{
	Memento* prevState = history.popHistory(); //take the last operation and create an object of the current state class memento 
	if(prevState != nullptr) {
		undoHelper(prevState);
		delete prevState;
	}
}

// Prints the list
void StringList::print() const
{
	for (int i = 0; i < n; i++) {
		cout << arr[i] << endl;
	}
}

// Helper function for checking index bounds.
void StringList::checkBounds(int i, string s) const
{
	if (i < 0 || i >= size()) {
		throw out_of_range("StringList::" + s + " index out of bounds");
	}
}

// POST: Doubles the capacity of the list if n == capacity
void StringList::checkCapacity()
{
	if (n == capacity) {
		capacity *= 2;
		string* temp = new string[capacity];
		
		for (int i = 0; i < n; i++) {
			temp[i] = arr[i];
		}
		delete[] arr;
		arr = temp;
	}
}

// Helper function to copy the contents of another list
void StringList::copyList(const StringList& lst)
{
	capacity = lst.capacity;
	n = lst.n;
	arr = new string[capacity];

	for (int i = 0; i < n; i++) {
		arr[i] = lst.arr[i];
	}
}

/* previous state and current state implementations start here */

// Memento is the current state 
	// CONSTRUCTOR
StringList::Memento::Memento(string* stringList, int size, int capacity) 
{
	currentSize = size;
	currentCapacity = capacity;
	stringListState = new string[capacity]; 
	//Handle bad_alloc
	if(stringListState == nullptr) {
	cout << "stringListState error: bad_alloc" << endl;
	delete[] stringListState;
	exit(1);
	 }
	for(int i = 0; i < currentSize; i++) {
		stringListState[i] = stringList[i];
	}
}

	// Destructor
StringList::Memento::~Memento() {
	if(stringListState != nullptr) {
		delete[] stringListState;
	}
}

	// Accessor
string* StringList::Memento::getState() const
{
	return stringListState;
}	

int StringList::Memento::getSize() const 
{
	return currentSize;
}

int StringList::Memento::getCapacity() const 
{
	return currentCapacity;
}

// History is the previous state 

// Constructor
StringList::History::History() 
{
	top = -1;
	stackCapacity = 4;
	mementos = new Memento*[stackCapacity];
	//Handle bad alloc 
	if(mementos == nullptr) {
	 	cout << "mementos error: bad_alloc" << endl;
	 	delete[] mementos;
	 	exit(1);
	 }
}

// Destructor
StringList::History::~History()
{
	deleteHelper();
}

// Mutator 
void StringList::History::pushHistory(Memento* newMemento) {
	if(top + 1 == stackCapacity) resize();
	mementos[top + 1] = newMemento;
	top++;
}

StringList::Memento* StringList::History::popHistory() {
	if(top >= 0) {
		Memento* poppedMemento = mementos[top];
		top--;
		return poppedMemento;
	}
	else return nullptr;	
}

// Helper method resizing the history stack
void StringList::History::resize() {
	stackCapacity *= 2;
	Memento** resizedHistory = new Memento*[stackCapacity];
	//Handle bad_alloc
	if(resizedHistory == nullptr) {
	 	cout << "resizedHistory error: bad_alloc" << endl;
	 	exit(1);
	}
	for(int i = 0; i < stackCapacity/2; i++) 
		resizedHistory[i] = mementos[i];
	delete[] mementos;
	mementos = resizedHistory;
}

// Helper method to delete the History stack
void StringList::History::deleteHelper() {
	if(top >= 0) {
		for(int i = 0; i <= top; i++) 
			delete mementos[i];
	}
	delete[] mementos;
}

StringList::Memento* StringList::createMemento() {
	Memento* newMemento = new Memento(arr, n, capacity);
	if(newMemento == nullptr) {
		cout << "newMemento error: bad_alloc" << endl;
		delete newMemento;
		exit(1);
	}
	return newMemento;
}

void StringList::undoHelper(Memento* paramMemento) {
	delete[] arr;
	arr = new string[paramMemento->getCapacity()];
	if(arr == nullptr) {
		cout << "new arr error: bad_alloc" << endl;
		delete[] arr;
		exit(1);
	}
	
	for(int i = 0; i < paramMemento->getSize(); i++) {
		arr[i] = (paramMemento->getState())[i];
	}

	n = paramMemento->getSize();
	capacity = paramMemento->getCapacity();
} 
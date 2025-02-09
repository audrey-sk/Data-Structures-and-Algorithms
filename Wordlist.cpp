
#include "Wordlist.h"
#include <fstream>
#include <sstream>
#include <algorithm>
#include <stdexcept>
#include <iostream>
#include <iomanip>
using std::setprecision;
using std::fixed;
using std::ifstream;
using std::ofstream; 
using std::cout; 

// Prints useful statistics about the word list
void Wordlist::printStatistics() const
{
	cout << "Number of different words: " << differentWords() << endl;
	cout << "    Total number of words: " << totalWords() << endl;
	cout << "       Most frequent word: " << mostFrequent() << endl;
	cout << "     Number of singletons: " << singletons()
		<< setprecision(0) << fixed
		<< " (" << 100.0 * singletons() / differentWords() << "%)"
		<< endl;
} 
// default constructor to make a null root and size 0 tree
Wordlist::Wordlist() : root(nullptr), size(0) {}

Wordlist::Wordlist(const std::string& filename) : root(nullptr), size(0) {
    std::ifstream file(filename);
    if (!file.is_open()) { //if file cant be opened
        throw std::invalid_argument("File not found: " + filename);
    }
    std::string word;
    while (file >> word) {
        //if(!word.empty()) //read each word
        insert(word); //insert word into the tree 
    }
    file.close();
}

Wordlist::Wordlist(const Wordlist& other) : root(nullptr), size(0) {
    deepCopy(root, other.root, nullptr); //copy constructor 
    size = other.size;
}
// assignmen operator
Wordlist& Wordlist::operator=(const Wordlist& other) {
    if (this != &other) { //self assignment check
        clear(root); //delete everything
        root = nullptr;
        size = 0;
        deepCopy(root, other.root, nullptr);
        size = other.size;
    }
    return *this;
}
// destructor 
Wordlist::~Wordlist() {
    clear(root);
}
// Helper functions
//return height of a node 
int Wordlist::getHeight(AVLTreeNode* node) const {
    return node ? node->height : -1;
}
// find the height difference between left and right subtree used to check height variant for AVL tree
int Wordlist::getBalanceFactor(AVLTreeNode* node) const {
    return (getHeight(node->left) - getHeight(node->right));
}

AVLTreeNode* Wordlist::rotateLeft(AVLTreeNode* node) {
    AVLTreeNode* newRoot = node->right;
    node->right = newRoot->left;
    if (newRoot->left) newRoot->left->parent = node;
    newRoot->left = node;

    newRoot->parent = node->parent;
    node->parent = newRoot;

    node->height = std::max(getHeight(node->left), getHeight(node->right)) + 1;
    newRoot->height = std::max(getHeight(newRoot->left), getHeight(newRoot->right)) + 1;

    return newRoot;
}

AVLTreeNode* Wordlist::rotateRight(AVLTreeNode* node) {
    AVLTreeNode* newRoot = node->left;
    node->left = newRoot->right;
    if (newRoot->right) newRoot->right->parent = node;
    newRoot->right = node;

    newRoot->parent = node->parent;
    node->parent = newRoot;

    node->height = std::max(getHeight(node->left), getHeight(node->right)) + 1;
    newRoot->height = std::max(getHeight(newRoot->left), getHeight(newRoot->right)) + 1;

    return newRoot;
}
//clear the whole tree 
void Wordlist::clear(AVLTreeNode* node) {
    if (node == nullptr) return;
    clear(node->left);
    clear(node->right);
    delete node;
}
// deep copy
void Wordlist::deepCopy(AVLTreeNode*& destRoot, AVLTreeNode* sourceRoot, AVLTreeNode* parent) {
    if (sourceRoot == nullptr) return;

    destRoot = new AVLTreeNode(sourceRoot->word);
    destRoot->count = sourceRoot->count;
    destRoot->height = sourceRoot->height;
    destRoot->parent = parent;

    deepCopy(destRoot->left, sourceRoot->left, destRoot);
    deepCopy(destRoot->right, sourceRoot->right, destRoot);
}
//find min value which is he left most node 
AVLTreeNode* Wordlist::findMinNode(AVLTreeNode* node)const{ 
	while(node!=nullptr && node->left!=nullptr){
	node=node ->left;}
	return node;
}
// helper for insertion into the tree recursively 
AVLTreeNode* Wordlist::insertHelper(AVLTreeNode* node, const std::string& word){
	if(node==nullptr){ //insert as a leaf  
		size++; 
        return new AVLTreeNode(word); 
	}
	if(word < node->word){ //go left
		node->left=insertHelper(node->left, word);
		node->left->parent=node;
	}else if(word > node->word){ //go right
		node->right=insertHelper(node->right, word);
		node->right->parent=node;
	}else{ //if its equal to the word add 1 to its count 
		node->count++;
		return node;
	}
	//update height and find balance factor
	node->height = std::max(getHeight(node->left), getHeight(node->right)) + 1;
    int balance = getBalanceFactor(node);
	// left rotation
	if (balance < -1 && word > node->right->word){ 
	return rotateLeft(node);}
	//right rotation
	if (balance > 1 && word < node->left->word){ //left heavy 
		return rotateRight(node); 
	}
	// LR rotation
	if (balance > 1 && word > node->left->word) {  
        node->left = rotateLeft(node->left);
        return rotateRight(node);
    }
	//RL rotation 
    if (balance < -1 && word < node->right->word) {
        node->right = rotateRight(node->right);
        return rotateLeft(node);
    }
	return node; 
}
void Wordlist::insert(const std::string& word){
	root = insertHelper(root,word); 
}
//Helper function ro romove 
	AVLTreeNode* Wordlist::removeHelper(AVLTreeNode* node, const std::string& word) {
    if (node == nullptr) return nullptr;  // Base case: word not found.

    // Search for the word to remove.
    if (word < node->word) {
        node->left = removeHelper(node->left, word);  
    } else if (word > node->word) {
        node->right = removeHelper(node->right, word); 
    } else {
        // Word is found. Handle the node removal.

        if (!node->left || !node->right) {  // Case 1: Node has 0 or 1 child.
            AVLTreeNode* temp = node->left ? node->left : node->right;
            if (temp) {
                temp->parent = node->parent;  
            }
            delete node;
            size--;  // Decrease size.
            return temp;  // Return the child 
        }

        // Case 2: Node has 2 children.
        AVLTreeNode* successor = findMinNode(node->right);  // Find the successor (leftmost node in right subtree)
        node->word = successor->word;  
        node->count = successor->count;
        node->right = removeHelper(node->right, successor->word);  // remove the successor
    }

    // Update the height and balance 
    node->height = std::max(getHeight(node->left), getHeight(node->right)) + 1;

    // Balance the node if necessary 
    int balance = getBalanceFactor(node);
    if (balance > 1 && getBalanceFactor(node->left) >= 0) {
        return rotateRight(node);  // Left heavy, do right rotation
    }
    if (balance > 1 && getBalanceFactor(node->left) < 0) {
        node->left = rotateLeft(node->left);  // LR rotation 
        return rotateRight(node);
    }
    if (balance < -1 && getBalanceFactor(node->right) <= 0) {
        return rotateLeft(node);  // Right heavy, do left rotation
    }
    if (balance < -1 && getBalanceFactor(node->right) > 0) {
        node->right = rotateRight(node->right);  // RL rotation
        return rotateLeft(node);
    }

    return node;  
}


bool Wordlist::remove(const std::string& word){
	if(!contains(word)){
		return false;
	}else{
		root=removeHelper(root, word);
		return true; 
	}
}
// get count
int Wordlist::getCount(const std::string& word){
AVLTreeNode* node = root;
while(node != nullptr){
	if(node -> word == word){
		return node -> count; 
	}
	if(word < node -> word){ //go left
		node = node -> left;
	}else{ //go right
		node = node -> right; 
	}
}
return 0; 
}


//contains
bool Wordlist::contains(const std::string& word){
	if (getCount(word) > 0){
		return true;
	}else{
		return false; 
	}

}

// number of distinct words
int Wordlist::differentWords()const{
	return size; 
}

// total number of words
int Wordlist::totalWordsHelper(AVLTreeNode* node) const{
	if(node==nullptr) return 0;
	//total nodes of right subtree + total nodes of left subtree
	return node->count + totalWordsHelper(node->left) + totalWordsHelper(node->right); 
}
int Wordlist::totalWords() const{
	return totalWordsHelper(root); 
}

// word that appears most frequently 
void Wordlist::mostFrequentHelper(AVLTreeNode* node, std::string& maxWord, int& maxCount) const{
	if(node == nullptr) return; 
	if(node -> count > maxCount){ //a new word with frequency more than the current one has been found 
		maxCount = node -> count;
		maxWord = node -> word; 
	}
	// do recursion for left and right sub trees 
	mostFrequentHelper( node -> left, maxWord , maxCount);
	mostFrequentHelper( node -> right, maxWord, maxCount); 
}
std::string Wordlist:: mostFrequent() const{
	if(root == nullptr){
		throw std::invalid_argument("Wordlist is empty!"); }
		int maxCount =0;
		std::string maxWord; 
		mostFrequentHelper(root, maxWord, maxCount); 
		return maxWord + " " + std::to_string(maxCount);
}
//Singeltons 
int Wordlist::singletons()const{
    int result = 0;
    countSingletons(root, result);
    return result;
}

void Wordlist::countSingletons(AVLTreeNode* node, int& result)const {
    if (node == nullptr) {
        return;  // Base case: no more nodes to visit
    }
    
    // Check if the current node is a singleton (count == 1)
    if (node->count == 1) {
        result++;  // Increment result if it's a singleton
    }
    
    // Recursively check left and right subtrees
    countSingletons(node->left, result);
    countSingletons(node->right, result);
}

//Printing
void Wordlist::printWords() const {
    int index = 1;
    printWordsHelper(root, index);
}

void Wordlist::printWordsHelper(AVLTreeNode* node, int& index) const {
    if (node == nullptr) return;
    printWordsHelper(node->left, index);
    std::cout << index++ << ". " << node->word << " " << node->count << '\n';
    printWordsHelper(node->right, index); 
}


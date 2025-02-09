
#pragma once
#include <string>
#include <iostream>
using std::string;
using std::cin;
using std::cout;
using std::endl;

class AVLTreeNode {
public:
	// Should have attributes named:
	// parent - pointer to parent
	// left - pointer to left child
	// right - pointer to right child
	// word - node's string data
	// count - number of times the word appears
	// height - node's height

    AVLTreeNode * parent;
    AVLTreeNode* left;
    AVLTreeNode* right;
    std:: string word; 
    unsigned int count;
    unsigned int height; 
    // Constructors ...
    AVLTreeNode(const std::string& word):
    word(word),count(1),height(0),parent(nullptr), left(nullptr), right(nullptr) {} 
};

// Wordlist class
class Wordlist
{
private:
	// Class attributes go here
	// Your class MUST have a root node named root (below)
	AVLTreeNode* root; // DO NOT REMOVE
    unsigned int size;

    // Helper methods
    int getHeight(AVLTreeNode* node) const;
    int getBalanceFactor(AVLTreeNode* node) const;
    AVLTreeNode* rotateLeft(AVLTreeNode* node);
    AVLTreeNode* rotateRight(AVLTreeNode* node);
    AVLTreeNode* insertHelper(AVLTreeNode* node, const std::string& word);
    AVLTreeNode* removeHelper(AVLTreeNode* node, const std::string& word);
    int totalWordsHelper(AVLTreeNode* node) const; 
    void mostFrequentHelper(AVLTreeNode* node, std::string& maxWord, int& maxCount) const; 
    void countSingletons(AVLTreeNode* node, int& result)const;
    AVLTreeNode* findMinNode(AVLTreeNode* node) const;
    void clear(AVLTreeNode* node);
    void deepCopy(AVLTreeNode*& destRoot, AVLTreeNode* sourceRoot, AVLTreeNode* parent);
    void printWordsHelper(AVLTreeNode* node, int& index) const; 

public:
	// public methods go here
    Wordlist();
    ~Wordlist();
    Wordlist(const std::string& filename);
    Wordlist(const Wordlist& other);
    Wordlist& operator=(const Wordlist& other); 
    void insert(const std::string& word);
    bool remove(const std::string& word);
    int getCount(const std::string& word);
    bool contains (const std::string& word);
    int differentWords() const;
    int totalWords() const;
    std::string mostFrequent()const;
    int singletons() const;
    void printWords()const; 


	// Prints useful statistics about the word list
	void printStatistics() const;

	// Returns the root of the AVL tree
	AVLTreeNode* getRoot() const { return root; }; // DO NOT REMOVE
};
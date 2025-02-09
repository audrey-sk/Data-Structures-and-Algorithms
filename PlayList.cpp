
#include "PlayList.h"
#include <stdexcept> 

// PlayList method implementations go here
// Default constructor
PlayList::PlayList() : head(nullptr), songcount(0) {}

// Copy constructor
PlayList::PlayList(const PlayList& pl) {
    if (pl.head == nullptr) {
        head = nullptr;
        songcount = 0;
        return;
    }
    head = new PlayListNode(pl.head->song);
    PlayListNode* current = head;
    PlayListNode* copiedCurrent = pl.head->next;

    while (copiedCurrent != nullptr) {
        current->next = new PlayListNode(copiedCurrent->song);
        current = current->next;
        copiedCurrent = copiedCurrent->next;
    }

    songcount = pl.songcount;  
}


// Destructor
PlayList::~PlayList() {
    while (head != nullptr) {
        PlayListNode* temp = head;
        head = head->next;
        delete temp;
    }
    songcount = 0;
}
// Assignment operator 
PlayList& PlayList::operator=(const PlayList& other) {
    if (this != &other) {
        
    while (head != nullptr) {
        PlayListNode* temp = head;
        head = head->next;
        delete temp;
    }
    songcount = 0;

    if (other.head != nullptr) {
        head = new PlayListNode(other.head->song);
        PlayListNode* current = head;
        PlayListNode* copiedCurrent = other.head->next;
        while (copiedCurrent != nullptr) {
            current->next = new PlayListNode(copiedCurrent->song);
            current = current->next;
            copiedCurrent = copiedCurrent->next;
            }
        }
    songcount = other.songcount;
    }
    return *this;
}



// Insert song at a specific position
void PlayList::insert(Song sng, unsigned int pos){
    if (pos > songcount) {
        throw std::out_of_range("Position out of range");
    }
    PlayListNode* newsong = new PlayListNode(sng);
    if (pos == 0) {
        newsong->next = head;
        head = newsong; 
    }else{
        PlayListNode* current = head; 
        PlayListNode* previous = nullptr; 
        for(unsigned int i=0; i<pos; i++){ 
            previous=current;
            current=current->next;
        }
        previous-> next = newsong;
        newsong->next=current; 
    }
    songcount++;  

}


// Get song at a specific position
Song PlayList::get(unsigned int pos) const {
    if (pos >= songcount) {
        throw std::out_of_range("Position is out of range of the PlayList");
    }
    PlayListNode* current = head;
    for (unsigned int i = 0; i < pos; i++) {
        current = current->next;
    }
    return current->song; 

}

// Remove song at a specific position
Song PlayList::remove(unsigned int pos){
    if (pos > songcount) {
        throw std::out_of_range("Position is out of range of the PlayList");
    }
    PlayListNode* current = head;   
    Song songtoremove = current -> song; 
    if (pos ==1){
        songtoremove=current -> song;
        head=current->next;
        delete current;  
    }else{
        PlayListNode* previous=nullptr;
        for(unsigned int i=1; i<pos; i++){
            previous=current;
            current=current->next;
        }
        songtoremove=current->song;
        previous->next = current->next; 
        delete current;
    }
    songcount--;
    return songtoremove; 

}

// Swap two songs
void PlayList::swap(unsigned int pos1, unsigned int pos2){
    if(pos1>=songcount || pos2>=songcount){
        throw std::out_of_range("Position out of range");
    }
    if (pos1 > pos2) {
        std::swap(pos1, pos2);
    }
    PlayListNode* previous1 = nullptr;
    PlayListNode* previous2 = nullptr;
    PlayListNode* firstswap = head;
    PlayListNode* secondswap = head;
    for(unsigned int i=0; i<pos1; i++){
        previous1= firstswap; 
        firstswap=firstswap -> next;
    }
    for (unsigned int i=0; i<pos2; i++){
        previous2 = secondswap;
        secondswap = secondswap->next;
    }
    if (previous1 != nullptr) {
        previous1->next = secondswap;
    } else {
        head = secondswap;
    }
    if (previous2 != nullptr) {
        previous2->next = firstswap;
    } else {
        head = firstswap;
    }
    // Swap 
    PlayListNode* temp = firstswap->next;
    firstswap->next = secondswap->next;
    secondswap->next = temp;
}

// Return the number of songs in the playlist 
unsigned int PlayList::size() const{
    return songcount; 
}


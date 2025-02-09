
/*Playlist Function Commands
Default constructor:
The default constructor only initializes the `head` to `nullptr` and `songcount` to 0. This is a constant-time operation.
Destructor: 
The destructor iterates through the entire playlist to delete each node. In the worst case, it needs to traverse and delete all nodes.
Copy constructor: 
The copy constructor has to iterate through the entire list to create a copy, making it linear in the number of songs `n`.
Overloaded assignment operator: 
The assignment operator deletes the current list and creates a new copy of the other list. Both the deletion and copying are O(n).
Insert: 
Inserting at position 0 (at the head) is O(1), but in the worst case, inserting at the end of the list requires traversing the entire list, which is O(n).
Remove: 
Removing a song at position 0 is O(1), but in the worst case, removing a song at the end requires traversing the list, which is O(n).
Get: 
Retrieving a song requires traversing the list up to the specified position, which in the worst case (last position) requires traversing all elements.
Swap: 
To swap two songs, the function must traverse the list twice to find the two songs at positions `pos1` and `pos2`, making it O(n) in the worst case.
Size: 
The size method simply returns the value of `songcount`, which is maintained throughout the program, making it a constant-time operation.
Main Function Commands
    Enter a song 
    Remove a song 
    Swap two songs 
    Print all the songs */


#include <iostream>
#include "PlayList.h"
#include "Song.h" 
#include <string> 
using std::cout;
using std::cin; 
using std::swap; 
void printPlayList(const PlayList& playlist){
    for (unsigned int i=0; i<playlist.size(); i++){
        Song currentsong = playlist.get(i);
        cout<< i+1<< " " << currentsong.getName() << " (" 
            << currentsong.getArtist() << ") "
            << currentsong.getLength() << "s\n";
    }
    cout<<"There are " << playlist.size() << " songs in the play list.\n";
    return; 
}
int main(){
    PlayList playlist; 
    int choice =0;
    cout << "Menu:\n"
            << "1 - Enter a song in the play list at a given position\n"
            << "2 - Remove a song from the play list at a given position\n"
            << "3 - Swap two songs in the play list\n"
            << "4 - Print all the songs in the play list\n"
            << "5 - Quit\n"; 
    while (choice!=5){ 
        cout<< "\nEnter 1 (insert), 2 (remove), 3 (swap), 4 (print) or 5 (quit):";
        cin>> choice; 
        if(choice ==1){
            int position=0;
            int len =0;
            string name , artist; 
            cout << "Song name: ";
            cin.ignore(); //to ignore newline at the end 
            getline(cin , name); 
            cout<< "Artist: "; 
            getline(cin, artist);
            cout<< "Length: ";
            cin>> len; 
            if((playlist.size())==0){
                cout<<"Position (1):";
            }else{ 
            cout<< "Position (1 to " << (playlist.size()+1) << "): ";  } 
            cin >> position; 
            playlist.insert(Song(name, artist, len), position-1 );
            cout << "You entered " <<name << " at position " << position << " in the play list\n"; 


        }
        else if (choice ==2){
            int position = 0; 
            cout<< "Position (1 to " << playlist.size() << "): ";  
            cin >> position; 
            Song removedsong = playlist.remove(position);
            cout << "Your removed "<<removedsong.getName()<<" from the play list\n"; 
            
        }

        else if (choice ==3){
            int position1 = 0;
            int position2 = 0;
            cout<< "Swap song at position (1 to " << playlist.size() << "): ";
            cin >> position1; 
            cout << "with the song at position (1 to " << playlist.size() << "): "; 
            cin >> position2; 
            if(position1==position2){
                cout<<"Can not swap same position\n"; 
            }else{ 
            playlist.swap(position1-1 , position2-1);
            cout << "You swapped the songs at positions " <<position1<< " and " <<position2 <<"\n"; }
        }

        else if (choice ==4){
            printPlayList(playlist);}

        else if (choice==5){
            cout<< "You have chosen to quit the program.\n"; 
        }
        if (choice > 5 || choice<1) {
            cout << "Invalid choice, please enter a valid option.\n";
        
        }
    }  
    
    return 0; 
} 






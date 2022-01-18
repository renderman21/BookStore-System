#include <iostream>
#include <stdlib.h>
#include "book.hpp"

using namespace std;

void mainMenu();

#define CLEARSCRN system("clear")

int loop = 1;

int main(){
    
    while(loop != 0){
        mainMenu();
    }
    
    return 0;
}

void mainMenu(){
      string enteredBookName;
    int   enteredBookPrice;
    int choice;
    bool isAvail;

    CLEARSCRN;

    cout << "WELCOME TO BOOKSTORE" << endl;
    cout << "HERE ARE THE LISTED BOOKS\n" << endl;

    printListBooks();

    cout << "\nTHERE ARE "<< bookCount() << " BOOKS AVAILABLE" <<endl;

    cout << "-----------------------" << endl; 
    cout << "What do you want to do?" << endl;
    cout << "-----------------------" << endl;

    cout << "[1]   ADD  BOOK " <<endl;
    cout << "[2]   PURCHASE BOOK" <<endl;
    cout << "[3]   SEARCH BOOK" << endl;
    cout << "[4]   QUIT" <<endl;

    do{
        cout << "What is your choice: ";
        cin >> choice; 
    }while(choice != 1 && choice != 2 
          && choice != 3 && choice != 4);

    switch (choice)
    {
    case 1:
        cout << "What is the name of the book? ";
        cin >> enteredBookName;
        cout << "How much is this book? ";
        cin >> enteredBookPrice;

        isAvail = isBookAvail(enteredBookName);

        if (!(isAvail)){addBook(enteredBookName, enteredBookPrice);}
        else {
            cout << "The book you entered is in the database. Please make another one" << endl; getchar(); getchar();}
        break;

    case 2:
        cout << "What book do you want to buy? ";
        cin >> enteredBookName;

        removeBook(enteredBookName);
        break;

    case 3:
        cout << "What is the name of the book that you want to find?";
        cin >> enteredBookName;

        searchBook(enteredBookName);
        break;
    
    case 4:
        loop = 0;
        cout << "Thank you for shopping!" << endl;
        break;
    }

}
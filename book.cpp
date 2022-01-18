#include <iostream>
#include <time.h>
#include <fstream>
#include <stdlib.h>
#include <algorithm>
#include <cctype>

#include "book.hpp"

#define OPEN_FILE fstream file("data.txt", ios_base::in);
#define OPEN_TEMP_FILE ofstream temp("new_data.txt");

#define CLOSE_FILE file.close();
#define CLOSE_TEMP_FILE temp.close();

using namespace std;

/*DESCRIPTION:  This will add the book to the 
                file name. During the process,
                the genID is called, giving it
                it's personal ID.
  @param       bookName is a string 
                that the book is being
                manipulated.
  @param       bookPrice is the price
               being made by the customer
*/
void addBook(string bookName, int bookPrice){

  int lenght;

  fstream file("data.txt", ios::out | ios_base::app);

  bookName = upperString(bookName);

  file.seekg(0, file.end);
  lenght = file.tellg();
  file.seekg(0, file.beg);

  file << genID();
  file << ' ';
  file << bookName;
  file << ' ';
  file << "P" << to_string(bookPrice) << endl;

  CLOSE_FILE;

}

/*DESCRIPTION:  This will return the number
                of books stored in the file.
                It will be went through
                a for loop by the number of
                IDs stored in the file. 
  @return       Integer
*/
int bookCount(){
  int count = 0;
  string tempString;

  OPEN_FILE;

  while (getline(file, tempString)){count++;}

  CLOSE_FILE;

  return count;
}

/*DESCRIPTION:  This will remove the books. It
                will remove the book name, ID, 
                and price from the file.
  @param        bookName is a string 
                that is being referred to.
*/
void removeBook(string bookName){
  
  bookName = upperString(bookName);

  string toTempFile;
  char confirmation;
  size_t found;
  bool isAvail;

  OPEN_FILE;
  OPEN_TEMP_FILE;

  isAvail = isBookAvail(bookName);

  if (isAvail){

    puts("The book is available");

    do { 
      printf("Do you confirm? Y/N ");
      scanf(" %c", &confirmation);
      confirmation = upperChar(confirmation);
    } while (confirmation != 'Y' && confirmation != 'N');

    if (confirmation == 'Y'){

      while (getline(file, toTempFile)){
        found = toTempFile.find(bookName);

        if(found == string::npos)
          temp << toTempFile << endl; 
      }

      CLOSE_TEMP_FILE;
      CLOSE_FILE;

      //Remove the files into a new one.
      remove("data.txt");
      rename("new_data.txt", "data.txt");

      cout << "You bought the item! Thank you!" << endl;
    }

    CLOSE_TEMP_FILE;
    CLOSE_FILE;
  }
  else {
    cout << "Please input the correct name. Make sure it has no spaces" << endl;
    CLOSE_FILE;
    CLOSE_TEMP_FILE;
  }

}

/*DESCRIPTION:  This will search for the book.
                A check must be passed if the
                bookName is available
                in the file. If it is not 
                available, it throw off
                an error. 
  @param        bookName is the string 
                that the book is being reffered
                to.
*/
void searchBook(string bookName){
  
  bookName = upperString(bookName);

  bool isAvail;

  isAvail = isBookAvail(bookName);

  if (isAvail){
    cout << "The book that you are looking for is available" << endl;
  }
  else{
    cout << "Please enter the correct name. Make sure there are no spaces" << endl;
  }

}

/*DESCRIPTION:  This will check if the ID 
                is being used
  @param        ID - is the integer that will
                check if it's avaialble.
  @return       An integer: (1) true,(0) false
*/
static bool isIdentificationUsed(int ID){
  OPEN_FILE;

  string referencedID;
  bool result;
  
  while (getline(file, referencedID, ' ')){
    if (referencedID == to_string(ID)){
      result = true; 
      break;
    }
    else {
      result = false;
      }
  }

  CLOSE_FILE;
  return result;
}

/*DESCRIPTION:  This will make the string into
                an uppercase for uniformity.
  @param        bookName - is a string
                that is being referred to.
  @return      A capatilized version of the
                bookName
*/
string upperString(string bookName){

  transform(bookName.begin(), bookName.end(), 
            bookName.begin(), ::toupper);

  return bookName;
}

/* DESCRIPTION: This will generate ID's, and must 
                undergo some kind of check
                if it's available; if not, 
                reloop.
   @return      A number generated ID
*/
static int genID(){
  
  int ID; bool isUsed;

  srand(time(NULL));

  do{
    ID = rand() % 1000; 

    isUsed = isIdentificationUsed(ID);
  } while(isUsed == true);

  return ID;
}

/*
  DESCRIPTION:  As like the upperString, it makes the 
                charactes to become uppercase;
                this is to make the choices to be 
                made uniformly.
  @param        ch is a character.
  @return       An uppercase version of ch
*/
static char upperChar(char ch){
  if (ch >= 'a' && 'z' >= ch){
    ch -= 32;
  }
  return ch;
}

/*
  This prints out the list  of books available.
*/
void printListBooks(){
  OPEN_FILE;
  string printOut;

  cout << "ID   NAME    PRICE" << endl;
  while (getline(file, printOut)) cout << printOut << endl;
  CLOSE_FILE;
}

/*
  DESCRIPTION:  This checks if the book is available.

  @param        bookName is the name being referred to
                and will be passed through a getline thing.
  @return       A boolean value.

*/
bool isBookAvail(string bookName){
  OPEN_FILE;

  bookName = upperString(bookName);
  string referredBookName;
  size_t found;

  bool result;

  result = false;

  while(getline(file, referredBookName)){
    found = referredBookName.find(bookName);

    if(found != string::npos){
      result = true;
      break;
    }
  }

  return result;

}

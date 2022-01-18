
#ifndef BOOK_H
#define BOOK_H

#include <string>
#include <fstream>

using namespace std;

void addBook (string bookName, int bookPrice); 
int bookCount();
void removeBook(string bookName);
void searchBook(string bookName);
static int genID();
string upperString(string bookName);
static bool isIdentificationUsed(int ID); 
static char upperChar(char ch);
void printListBooks();
bool isBookAvail(string bookName);

    

#endif /* BOOK_H */
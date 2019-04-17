#include "book.h"
using namespace std;
Book::Book(int id, string bookName, string auth, string cat) {
   bookID = id;
   title = bookName;
   author = auth;
   category = cat;
   
   
}

string Book::getTitle() {
    return title; 
}

string Book::getAuthor() {
    return author; 
}

string Book::getCategory() {
    return category; 
}

int Book::getId() {
    return bookID; 
}
void Book::setPersonPtr(Person * ptr) {
    personPtr = ptr;
} 

Person * Book::getPersonPtr() {
    return personPtr;
}
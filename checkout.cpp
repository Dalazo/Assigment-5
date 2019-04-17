// Name
// Section #
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include "book.h"
#include "person.h"
using namespace std;

void printMenu() {
    cout << "----------Library Book Rental System----------" << endl;
    cout << "1.  Book checkout" << endl;
    cout << "2.  Book return" << endl;
    cout << "3.  View all available books" << endl;
    cout << "4.  View all outstanding rentals" << endl;
    cout << "5.  View outstanding rentals for a cardholder" << endl;
    cout << "6.  Open new library card" << endl;
    cout << "7.  Close library card" << endl;
    cout << "8.  Exit system" << endl;
    cout << "Please enter a choice: ";
}


Book * searchBook(vector<Book *> mybooks, int ID);
Person * IDcheck(vector<Person*> card, int ID);
void readPersons(vector<Person*> &myvect, string name);
void readBooks(vector<Book*> &myvect, string name);
void OutstandingBooks(vector<Book*> &myvect);
void newPerson(vector<Person*> &myvect);
int askID();
void unrentedBooks(vector<Book*> &myvect);
int main()
{
    vector<Book *> books;
    vector<Person *> cardholders;
    

    readPersons(cardholders, "persons.txt");
   readBooks(books, "books.txt");



Person * Personptr = nullptr;
Book * Bookptr = nullptr;
string name;
int id;    
    int choice;
    do
    {
        // If you use cin anywhere, don't forget that you have to handle the <ENTER> key that 
        // the user pressed when entering a menu option. This is still in the input stream.
        printMenu();
        cin >> choice;
        switch(choice)
        {
            case 1:
                
                 
                Personptr = IDcheck(cardholders,askID());
                if (Personptr == nullptr)
                {

                    cout << "Person not found" << endl;
                break;
                }
                Bookptr = searchBook(books,askID());
                if (Bookptr == nullptr)
                {

                    cout << "Book not found" << endl;
                break;
                }
                
                Bookptr->setPersonPtr(Personptr);
                cout << "Rental Completed" << endl;
                
                break;


            case 2:
              Bookptr =  searchBook(books,askID());
                
              Bookptr->setPersonPtr(nullptr);
              cout << "Rental returned" << endl;
                break;

            case 3:
                
                unrentedBooks(books);
                break;

            case 4:
                OutstandingBooks(books);

                break;

            case 5:

                Personptr = IDcheck(cardholders,askID());
                if (Personptr == nullptr)
                {

                    cout << "Person not found" << endl;
                break;
                }
                for (int i = 0; i<books.size();i++)
                {

                    if (Personptr == books.at(i)->getPersonPtr())
                  {
                    cout << books.at(i)->getId() << endl;
                    cout << books.at(i)->getTitle() << endl;
                    cout << books.at(i)->getAuthor() << endl;
                
                  }
                  
                    
                }
                

                break;

            case 6:
                newPerson(cardholders);
                break;

            case 7:
                // Close library card
                break;
                
            case 8:
  
                break;

            default:
                cout << "Invalid entry" << endl;
                break;
        }
        cout << endl;
   } while(choice != 8);
     cout << "Clearing.." << endl;
     for (int i=0; i <cardholders.size(); i ++)
    {  
    delete cardholders.at(i);

    }
    cardholders.clear();
    for (int i=0; i <books.size(); i ++)
    {  
    delete books.at(i);

    }
     books.clear();

      return 0;
}









void readPersons(vector<Person*> &myvect, string filename)
{

fstream myfile;



    myfile.open(filename);
   if (!myfile.is_open())
   {
    std::cout << "file is not found. Please make sure file is available" << endl;

   }

    int cardID;
    bool active;
    string firstName;
    string lastName;
   
   
   while (!myfile.eof())

{   
    myfile >> cardID;
    myfile >> active;
    myfile >> firstName;
    myfile >> lastName;


myvect.emplace_back(new Person(cardID,active,firstName,lastName));

}

myfile.close();



}




void readBooks(vector<Book*> &myvect, string name)
{


fstream myfile2;



    myfile2.open(name);
   if (!myfile2.is_open())
   {
    cout << "file is not found. Please make sure file is available" << endl;

   }

    int bookID ;
    
    string Bookname;
    string Author;
   string category;
   
   string authorL;
   string empty;
   int counter = 0;
while (myfile2>>bookID)
{   
    getline(myfile2,empty);
    getline(myfile2,Bookname);
    getline(myfile2,Author);
    getline(myfile2,category);
    getline(myfile2,empty);

myvect.push_back(new Book(bookID,Bookname,Author, category));

myvect.at(counter)->setPersonPtr(nullptr);
counter++;
}
myfile2.close();


}

Person * IDcheck(vector<Person *> card, int ID)
{

for (int i = 0; i < card.size(); i++)
{

if (card.at(i)->getId() == ID)
{
cout << "Record found" << endl;
cout << "Customer Name:" << card.at(i)->fullName()<< endl;

Person * ptr = card.at(i);
return ptr;


}
}

return nullptr;


}

int askID()
{

int id;
cout << "Please enter ID: " << endl;
                cin.ignore();
                
                
                cin>> id;


return id;

}


Book * searchBook(vector<Book *> mybooks, int ID)
{



for (int i = 0; i < mybooks.size(); i++)
{

if (mybooks.at(i)->getId() == ID)
{
cout << "Book found" << endl;
cout << "Book title:" << mybooks.at(i)->getTitle() << endl;
cout << " " << endl;
Book * ptr = mybooks.at(i);
return ptr;



}

return nullptr;




}
}


void OutstandingBooks(vector<Book*> &myvect)
{

Person * ptr;

for (int i = 0; i < myvect.size(); i ++)
{


if (myvect.at(i)->getPersonPtr() != nullptr)
{
cout << " " << endl;
cout << myvect.at(i)->getId() << endl;
cout << myvect.at(i)->getTitle() << endl;
cout << myvect.at(i)->getAuthor() << endl;

ptr = myvect.at(i)->getPersonPtr();
cout << "Cardholder :" << ptr->fullName() << endl;
cout << "Card ID: " << ptr->getId() << endl;
}
}

}

void unrentedBooks(vector<Book*> &myvect)
{


for (int i = 0; i < myvect.size(); i ++)
{


if (myvect.at(i)->getPersonPtr() == nullptr)
{
cout << " " << endl;
cout << myvect.at(i)->getId() << endl;
cout << myvect.at(i)->getTitle() << endl;
cout << myvect.at(i)->getAuthor() << endl;


}
}
}


void newPerson(vector<Person*> &myvect)
{
string name;
string last;
int id;
bool active;
cout << "Please enter name" << endl;
cin >> name;
cout << "Please last name" << endl;
cin >> last;

id = 1 + myvect.back()->getId();
active = true;
myvect.push_back(new Person(id,active,name,last));

cout << "ID created " << name + " " + last << endl;
cout << active << endl;
cout << "ID number " << id;



}

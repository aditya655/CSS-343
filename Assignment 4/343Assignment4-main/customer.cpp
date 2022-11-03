//
// Created by zachc on 5/28/2022.
//

#include "customer.h"
#include <string>

using namespace std;

//Default constructor. Sets ID to 0000, firstName "Default", lastName "Default"
Customer::Customer()
{
   ID = 0000;
   firstName = "Default";
   lastName = "Default";
   numTransactions = 0;
}

Customer::~Customer()
{

}

Customer::Customer(int ID, std::string firstName, std::string lastName)
{
   this->ID = ID;
   this->firstName = firstName;
   this->lastName = lastName;
}

//Output the Customer's history to cout in chronological order.
//Format:
//typeOfHistory: movie.toString()
void Customer::outputHistory() const
{
   for(int i = 0; i < numTransactions; i++) {
      cout << historyTypes[i];
      cout << ": ";
      cout << historyMovies[i].toString();
      cout << "\n";
   }
}

void Customer::addHistory(Movie movie, std::string type)
{
   if(numTransactions >= MAXHISTORY) {
      cout << "numTransactions cannot exceed MAXHISTORY";
      return;
   }
   historyMovies[numTransactions] = movie;
   historyTypes[numTransactions] = type;
   numTransactions++;
}

int Customer::getID() const
{
   return ID;
}

string Customer::getFirstName() const
{
   return firstName;
}

string Customer::getLastName() const
{
   return lastName;
}
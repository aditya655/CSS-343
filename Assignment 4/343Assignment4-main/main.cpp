#include <iostream>
#include <fstream>
#include "customer.h"
#include "hashtable.h"
#include "comedy.h"
#include "drama.h"
#include "classic.h"

using namespace std;

int main()
{
  ifstream customerFile("data4customer.txt");
  ifstream moviesFile("data4movies.txt");
  ifstream transactionsFile("data4commands.txt");

      cout << "Hello" << endl;
  if (!customerFile)                
      cout << "Customer file cannot be oppened" << endl;
   if (!moviesFile)                   
      cout << "Movie file cannot be oppened" << endl;
   if (!transactionsFile)             
      cout << "Transaction file cannot be oppened" << endl;
   
  else {
		cout << "File created successfully!";
		
	}

   HashTable<Customer> customers;
   HashTable<Movie> movies;

   
	return 0;

  

  

  

}
#include "classic.h"
#include "movie.h"

Classic::Classic(int stock, string title, string director, string actor,
                 int releaseYear, int monthReleased)
{
   this->movieCode = 'C';
   this->title = title;
   this->stock = stock;
   this->director = director;
   this->actor = actor;
   this->releaseYear = releaseYear;
   this->monthReleased = monthReleased;
}

 Classic::Classic(){
   movieCode = 'C';
   stock = 0;
   releaseYear = 0;
   title = "";
   director = "";
   releaseYear = 0;
   monthReleased = 0;

   }

Classic::~Classic()
{

}

int Classic::getMonth() const
{
   return monthReleased;
}

string Classic::getActor() const
{
   return actor;
}

string Classic::toString() const
{
   return movieCode + " " + to_string(stock) + " " + director + " " + title +
          " " + actor + " " + to_string(monthReleased) + " " +
          to_string(releaseYear);
}

bool Classic::operator==(const Movie& compare) const
{
   if(monthReleased == compare.getMonth() &&
      releaseYear == compare.getYear() &&
      getActor() == compare.getActor())
   {
      return true;
   } else
   {
      return false;
   }
}

bool Classic::operator>(const Movie& compare) const
{
   if(releaseYear > compare.getYear())
   {
      return true;
   } else if(releaseYear == compare.getYear())
   {
      if(monthReleased > compare.getMonth())
      {
         return true;
      }
   }

   return false;

}

bool Classic::operator<(const Classic& compare) const
{
   if(releaseYear < compare.getYear())
   {
      return true;
   } else if(releaseYear == compare.getYear())
   {    //If release year is the same:
      if(monthReleased < compare.getMonth())
      {
         return true;
      } else if(monthReleased == compare.getMonth())
      {
         return (actor.compare(compare.getActor()) < 0);
      }
   }
   return false;

}

std::ostream& operator<<(ostream& output, const Classic& movie)
{
   output << movie.toString();
   return output;
}

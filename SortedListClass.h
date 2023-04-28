#ifndef _SORTEDLISTCLASS_H_
#define _SORTEDLISTCLASS_H_

#include "LinkedNodeClass.h"
#include <iostream>
using namespace std;

//Programmer: Nikki Perkins
//Date: April 2021
//Purpose: Sorts the nodes in a queue so that they can be accessed

template < class T >
class SortedListClass
{
  private:
    LinkedNodeClass< T > *head;
    LinkedNodeClass< T > *tail; 
 
  public:
    SortedListClass< T >();

    SortedListClass< T >(const SortedListClass< T > &rhs);

    ~SortedListClass< T >();

    void clear();

    void insertValue(const T &valToInsert);
    
    void printForward() const;
     
    void printBackward() const;

    bool removeFront(T &theVal);

    bool removeLast(T &theVal);

    T getNumElems() const;

    bool getElemAtIndex(const T index, T &outVal) const;
};

#include "SortedListClass.inl"
#endif

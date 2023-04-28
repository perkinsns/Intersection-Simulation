#ifndef _LINKEDNODECLASS_H_
#define _LINKEDNODECLASS_H_

#include<iostream>                      
using namespace std;                                                          

//Programmer: Nikki Perkins
//Date: April 2021
//Purpose: Connect nodes for the purpose of a queue system

template < class T >
class LinkedNodeClass
{
  private:
    LinkedNodeClass< T > *prevNode; 
    T nodeVal;               
    LinkedNodeClass< T > *nextNode;
  
  public:
    LinkedNodeClass< T >(LinkedNodeClass< T > *inPrev, const T &inVal,        
                    LinkedNodeClass< T > *inNext);

    T getValue() const;

    LinkedNodeClass< T >* getNext() const;
 
    LinkedNodeClass< T >* getPrev() const; 
 
    void setNextPointerToNull();
 
    void setPreviousPointerToNull();
 
    void setBeforeAndAfterPointers();
};

#include "LinkedNodeClass.inl"
#endif

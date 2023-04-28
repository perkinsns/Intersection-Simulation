#ifndef _FIFOQUEUECLASS_H_
#define _FIFOQUEUECLASS_H_

#include "LinkedNodeClass.h"
#include <iostream>
using namespace std;

//Programmer: Nikki Perkins
//Date: April 2021
//Purpose: First in, first out queue system

template <class T>
class FIFOQueueClass
{
  private:
    LinkedNodeClass< T > *head; 
    LinkedNodeClass< T > *tail; 

  public:
    FIFOQueueClass();
   
    ~FIFOQueueClass();

    void enqueue(const T &newItem);
         
    bool dequeue(T &outItem);
      
    void print() const;
                               
    int getNumElems() const;
                                   
    void clear();                                      
};

#include "FIFOQueueClass.inl"
#endif

template <class T>
FIFOQueueClass< T >::FIFOQueueClass()
{
  head = NULL;
  tail = NULL;
}

template <class T>
FIFOQueueClass< T >::~FIFOQueueClass()
{
  clear();
}

template <class T>
void FIFOQueueClass< T >::enqueue(const T &newItem)
{
  LinkedNodeClass< T >* newNode = NULL;
  //LinkedNodeClass< T >* previousNode = NULL;
  //LinkedNodeClass< T >* nextNode = NULL;
  newNode = new LinkedNodeClass< T >(NULL, newItem, head);
  head = newNode;
  newNode->setBeforeAndAfterPointers();
  if (tail == NULL)
  {
    tail = newNode;
  }
}

template <class T>
bool FIFOQueueClass< T >::dequeue(T &outItem)
{
  bool returnVal = false;
  if (tail != NULL)
  {
    if (head == tail)
    {
      outItem = tail->getValue();
      delete tail;
      head = NULL;
      tail = NULL;
    }
    else
    { 
      LinkedNodeClass< T >* temp = tail;
      outItem = temp->getValue();
      tail = tail->getPrev();
      tail->setNextPointerToNull();
      delete temp;
    }
    returnVal = true;
  }
  return (returnVal);
}

template <class T>
void FIFOQueueClass< T >::print() const
{
  for (LinkedNodeClass< T >* i = head; i != NULL; i = i->getNext())
  {
    cout << i->getValue() << " " ;
  }
  cout << endl;
}
                               
    //Returns the number of nodes contained in the queue.
template <class T>
int FIFOQueueClass< T >::getNumElems() const
{
  int counter = 0;
  for (LinkedNodeClass< T >* i = head; i != NULL; i = i->getNext())
  {
    counter++;
  }
  return (counter);
}
                                   
    //Clears the queue to an empty state without resulting in any
    //memory leaks.
template <class T>
void FIFOQueueClass< T >::clear()
{
  while(head != NULL)
  {
    LinkedNodeClass< T >* temp = head;
    head = head->getNext();
    delete temp;
  }
  tail = NULL;
}
                                      

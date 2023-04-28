template < class T >
SortedListClass< T >::SortedListClass()
{
  head = NULL;
  tail = NULL;
}

template < class T >
SortedListClass< T >::SortedListClass(const SortedListClass< T > &rhs)
{
  if (rhs.head != NULL)
  {
    T val;
    rhs.getElemAtIndex(0,val);
    head = new LinkedNodeClass< T >(NULL,val,NULL);
    tail = head;
    LinkedNodeClass < T >* current = head;
    for (int i = 1; i < rhs.getNumElems(); i++)
    {
      rhs.getElemAtIndex(i,val);
      tail = new LinkedNodeClass< T >(current,val,NULL);
      tail->setBeforeAndAfterPointers();
      current = tail;
    }
  }
  else
  {
    head = NULL;
    tail = NULL;
  }
}

template < class T >
SortedListClass< T >::~SortedListClass()
{
  clear();
}

template < class T >
void SortedListClass< T >::clear()
{
  while(head != NULL)
  {
    LinkedNodeClass< T >* temp = head;
    head = head->getNext();
    delete temp;
  }
  tail = NULL;
}

template < class T >
void SortedListClass< T >::insertValue(const T &valToInsert)
{
  bool nodeInserted = false;
  LinkedNodeClass< T >* previousNode = NULL;
  LinkedNodeClass< T >* nextNode = NULL;
  LinkedNodeClass< T >* newNode = NULL;
  if (head != NULL)
  {
    for (LinkedNodeClass< T >* i = head; i != NULL; i = i->getNext())
    {
      if (valToInsert <= i->getValue() && nodeInserted == false)
      {
        previousNode = i->getPrev();
        nextNode = i;
        nodeInserted = true;
      }
      else if (i->getNext() == NULL && nodeInserted == false)
      {
        previousNode = i;
        nextNode = NULL;
      }
    }
  }
  newNode = new LinkedNodeClass< T >(previousNode, valToInsert, nextNode);
  if (previousNode == NULL)
  {
    head = newNode;
  }
  if (nextNode == NULL)
  {
    tail = newNode;
  }
  newNode->setBeforeAndAfterPointers();
}

template < class T >
void SortedListClass< T >::printForward() const
{
  cout << "Forward List Contents Follow:" << endl;
  for (LinkedNodeClass< T >* i = head; i != NULL; i = i->getNext())
  {
    cout << "  " << i->getValue() << endl;
  }
  cout << "End Of List Contents" << endl;
}

template < class T >
void SortedListClass< T >::printBackward() const
{
  cout << "Backward List Contents Follow:" << endl;
  for (LinkedNodeClass< T >* i = tail; i != NULL; i = i->getPrev())
  {
    cout << "  " << i->getValue() << endl;
  }
  cout << "End Of List Contents" << endl;
}

template < class T >
bool SortedListClass< T >::removeLast(T &theVal)
{
  bool returnVal = false;
  if (tail != NULL)
  {
    if (head == tail)
    {
      head = NULL;
      tail = NULL;
    }
    else
    { 
      LinkedNodeClass< T >* temp = tail;
      theVal = temp->getValue();
      tail = tail->getPrev();
      tail->setNextPointerToNull();
      delete temp;
    }
    returnVal = true;
  }
  return (returnVal);
}

template < class T >
bool SortedListClass< T >::removeFront(T &theVal)
{
  bool returnVal = false;
  if (head != NULL)
  {
    LinkedNodeClass< T >* temp = head;
    theVal = temp->getValue();
    if (tail == head)
    {
      head = NULL;
      tail = NULL;
    }
    else
    {
      head = head->getNext();
      head->setPreviousPointerToNull();
    }
    delete temp;
    returnVal = true; 
  }
  return (returnVal);
}

template < class T >
T SortedListClass< T >::getNumElems() const
{
  int counter = 0;
  for (LinkedNodeClass< T >* i = head; i != NULL; i = i->getNext())
  {
    counter++;
  }
  return (counter);
}

template < class T >
bool SortedListClass< T >::getElemAtIndex(const T index, T &outVal) const
{
  bool returnVal = false;
  LinkedNodeClass< T >* pointAtIndex = head;
  if (getNumElems() == 0)
  {
    cout << "list empty" << endl;
  }
  else if (0 <= index && index < getNumElems())
  {
    if (pointAtIndex->getNext() != NULL)
    {
      for (int i = 0; i < index; i++)
      {
        pointAtIndex = pointAtIndex->getNext();
      }
    }  
    else
    {
      pointAtIndex = tail;
    }
    returnVal = true;
    outVal = pointAtIndex->getValue();
  }
  return (returnVal);
}


#include <galaxy-explorer/AsteroidList.hpp>

//Code for the default AsteroidListItem Constructor
//Sets data pointer and next pointer to null pointer
AsteroidListItem::AsteroidListItem() {
    this->next = nullptr;
    this->data = nullptr;
}

//Code constructs a new AsteroidListItem object and sets its data to Asteroid a data
AsteroidListItem::AsteroidListItem(Asteroid a) {
    this->next = nullptr;
    this->data = new Asteroid(a.getID(), a.getMass(), a.getHealth(),
                              a.getCurrentHitbox(), a.getVelocity());
}

//Deletes the dynamically created data
AsteroidListItem::~AsteroidListItem() { 
    delete this->data;
}

//The AsteroidList class calls the AsteroidListItem default constructor
//This initializes AsteroidListItem with next as null pointer and data as null pointer
AsteroidList::AsteroidList() {
//No need to do anything
}

//Copy constructor copies the src Asteroid List by copying each List Item
AsteroidList::AsteroidList(const AsteroidList& src) {
    AsteroidListItem *temp = &head;
    const AsteroidListItem *srcTemp = src.head.getNext();
    
    while(srcTemp != nullptr) {
        temp->setNext(new AsteroidListItem(srcTemp->getData()));
        temp = temp->getNext();
        srcTemp = srcTemp->getNext();
    }
}

//Destructor calls the clear function which clears the linked list before destruction
AsteroidList::~AsteroidList() {
    this->clear();
}

//If list is empty, function creates a new list item and head points to it
//If list exists, the new list item points to the current first item of the list
//Then head points to the new list item
void AsteroidList::pushFront(Asteroid e) {
    AsteroidListItem *newItem = new AsteroidListItem(e);
    if (head.getNext() == nullptr)
        head.setNext(newItem);
    
    else {
        newItem->setNext(head.getNext());
        head.setNext(newItem);
    }
}

//Function returns a reference to the first asteroid without protection to the reference
Asteroid& AsteroidList::front() {
    if (head.getNext() == nullptr)
        return *(Asteroid*)nullptr;
     
    return head.getNext()->getData();
}

//Function returns a reference to the first asteroid with protection to the reference
const Asteroid& AsteroidList::front() const {
    if (head.getNext() == nullptr)
        return *(Asteroid*)nullptr;
     
    return head.getNext()->getData();
}

//Boolean function evaluates true if head pointer is a null pointer
//Else this function evaluates false
bool AsteroidList::isEmpty() const {
    if (head.getNext() == nullptr) 
        return true;
    
    return false;
}

int AsteroidList::size() const {
    if (head.getNext() == nullptr)
        return 0;
    
    int size = 1;
    const AsteroidListItem *temp = head.getNext();
    while (temp->getNext() != nullptr) {
        size++;
        temp = temp->getNext();
    }
    return size;
}

//Return pointer to head without protecting the object
AsteroidListItem* AsteroidList::beforeBegin() {
    return &head;
}

//Return pointer to head with protection of the object so it can't be changed
const AsteroidListItem* AsteroidList::beforeBegin() const {
    return &head;
}

//If the list is empty, function returns null pointer
//Else the function returns the pointer to the first list item
//There is no protection of this pointer 
AsteroidListItem* AsteroidList::begin() {
    return head.getNext();
}

//If the list is empty, function returns null pointer
//Else the function returns the pointer to the first list item
//There is protection of this pointer and it can't be changed
const AsteroidListItem* AsteroidList::begin() const {
    return head.getNext();
}

//If the list is empty, function returns null pointer
//Else the function returns the pointer to the last list item
//There is no protection of this pointer
AsteroidListItem* AsteroidList::beforeEnd() {
    AsteroidListItem *temp = head.getNext();
    while (temp->getNext() != nullptr)
        temp = temp->getNext();
    return temp;
}

//If the list is empty, function returns null pointer
//Else the function returns the pointer to the last list item
//There is protection of this pointer and it can't be changed
const AsteroidListItem* AsteroidList::beforeEnd() const {
    const AsteroidListItem *temp = head.getNext();
    while (temp->getNext() != nullptr)
        temp = temp->getNext();
    return temp;
}

//Function always returns null pointer
//The last list item always points to a null pointer
//Empty list always returns null pointer
AsteroidListItem* AsteroidList::end() {
    return nullptr;
}

//Function always returns null pointer
//The last list item always points to a null pointer
//Empty list always returns null pointer
const AsteroidListItem* AsteroidList::end() const {
    return nullptr;
}

//Function adds a single asteroid to this list, in the position immediately after prev
//Function returns the item that was inserted 
AsteroidListItem* AsteroidList::insertAfter(AsteroidListItem* prev, Asteroid e) {
    if (prev == nullptr)
        return prev;  
    
    AsteroidListItem *newItem = new AsteroidListItem(e);
    if (prev->getNext() == nullptr) {    
        prev->setNext(newItem);
        return newItem;
    }
    
    else {
        newItem->setNext(prev->getNext());
        prev->setNext(newItem);
        return newItem;
    }
}

//Add independent copies of the entities in others to this list
//These are placed immediately after insertion_point, in the same order as others
//Returns the last item that was inserted, or insertion_point if others is empty
AsteroidListItem* AsteroidList::insertAfter(AsteroidListItem* prev, const AsteroidList& others) {
    if (prev == nullptr)
        return prev;  
    
    AsteroidListItem *temp = prev;
    const AsteroidListItem *othersTemp = others.head.getNext();
    while (othersTemp != nullptr) {
        insertAfter(temp, othersTemp->getData());
        othersTemp = othersTemp->getNext();
        temp = temp->getNext();
    }
    return temp;
}

//Function delete the asteroid following the previous item.
//Returns the list item that followed the erased item, or end() if there wasn't one.
//This function may have ANY BEHAVIOUR if there is no asteroid after prev
AsteroidListItem* AsteroidList::eraseAfter(AsteroidListItem* prev) {
    if (prev == nullptr)
        return end();
    else if(prev->getNext() == nullptr)
        return end();
    
    AsteroidListItem *temp = prev->getNext()->getNext();
    delete prev->getNext();
    prev->setNext(temp);
    return temp;
}

//Make the list empty by clearing the nodes one at a time until the end of list
void AsteroidList::clear() {
    AsteroidListItem *temp = head.getNext();
    while (temp != nullptr) {
        AsteroidListItem *copy = temp;
        temp = temp->getNext();
        delete copy;
    }
    head.setNext(nullptr);
    return;
}

//Makes this list an independent copy of src using deep assignments
//This means that there is NO shared data or pointers
AsteroidList& AsteroidList::operator=(const AsteroidList& src) {
    if (this == &src)
        return(*this);
    this->clear();
    this->insertAfter(&head, src);
    return (*this);
}

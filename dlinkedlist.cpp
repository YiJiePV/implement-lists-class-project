// Remember to write your headers!
/*
 * Title:		DoubleLinkedList Implementation
 * Purpose:		Definition of methods of a DoubleLinkedList class
 * Author:		Karena Qian
 * Date:		May 10, 2022
 */

#include "object.h"
#include "dlinkedlist.h"

#include <string>
#include<sstream>
using std::string;
using std::stringstream;

/**
 * Copy constructor
 * Create a deep copy of another DoubleLinkedList
 * @param other DoubleLinkedList
 */
DoubleLinkedList::DoubleLinkedList(const DoubleLinkedList &other): List(other), _head(nullptr), _tail(nullptr){
    for (Node* tmp = other._head; tmp != nullptr; tmp = tmp->next){
        Insert(tmp->data->Clone(), _size);
    }
}
/**
 * Copy Assignment Operator
 * Does nothing
 * @param rhs DoubleLinkedList
 * @return this to follow chain assignment standard
 */
DoubleLinkedList &DoubleLinkedList::operator=(const DoubleLinkedList &rhs) {
	return *this;
}
/**
 * Constructor
 * Creates an empty DoubleLinkedList
 */
DoubleLinkedList::DoubleLinkedList(): List(), _head(nullptr), _tail(nullptr){
}
/**
 * Destructor
 * Releases the memory used by the DoubleLinkedList
 */
DoubleLinkedList::~DoubleLinkedList() {
    Node *temp = _head;
    while(_head != nullptr){
        _head = temp->next;
        delete temp->data;
        delete temp;
        temp = _head;
    }
    _head = nullptr;
    _tail = nullptr;
    _size = 0;
}
/**
 * Insert
 * Insert a new Node with given element at given position in the DoubleLinkedList
 * @param element to be inserted in the DoubleLinkedList
 * @param position where the new Node is to be inserted
 * @return true, if the element is inserted successively, false otherwise
 */
bool DoubleLinkedList::Insert(Object *element, size_t position) {
    if(position > _size){ //invalid position
        return false;
    }
    Node *neo = new Node();
    neo->data = element;
    neo->next = nullptr;
    neo->previous = nullptr;
    if(_size == 0){ //if list is empty
        _head = neo;
        _tail = neo;
    }
    else if(position == 0){ //insert at the head
        neo->next = _head;
        _head->previous = neo;
        _head = neo;
    }
    else if(position == _size){ //insert at the tail
        neo->previous = _tail;
        _tail->next = neo;
        _tail = neo;
    }
    else {
        Node *before = _head;
        Node *after = _head->next;
        for (size_t i = 1; i < position; i++) {
            if(after->next == nullptr){
                break;
            }
            before = before->next;
            after = after->next;
        }
        //insert somewhere in the middle
        neo->previous = before;
        neo->next = after;
        before->next = neo;
        after->previous = neo;
    }
    _size++;
	return true;
}
/**
 * IndexOf
 * Returns the index of given element in DoubleLinkedList, if found
 * @param element to be found in the DoubleLinkedList
 * @return the index of given element if found, -1 otherwise
 */
int DoubleLinkedList::IndexOf(const Object *element) const {
    int index = 0;
    for(Node* temp = _head; temp != nullptr; temp = temp->next){
        if(temp->data->Equals(*element)){
            return index;
        }
        index++;
    }
	return -1;
}
/**
 * Remove
 * Remove a new Node at given position in the DoubleLinkedList
 * @param position where a Node is to be removed
 * @return the removed node's data if removed successfully, null otherwise
 */
Object *DoubleLinkedList::Remove(size_t position) {
    if(position > _size){ //invalid position
        return nullptr;
    }
    Object* object = nullptr;
    Node* remove = nullptr;
    if(position == 0){ //remove at the head
        object = _head->data;
        _head->data = nullptr;
        remove = _head;
        _head = _head->next;
        _head->previous = nullptr;
        remove->next = nullptr;
        delete remove;
    }
    else if(position == _size - 1){ //remove at the tail
        object = _tail->data;
        _tail->data = nullptr;
        remove = _tail;
        _tail = _tail->previous;
        _tail->next = nullptr;
        remove->previous = nullptr;
        delete remove;
    }
    else {
        Node *before = _head;
        remove = _head->next;
        Node *after = _head->next->next;
        for (size_t i = 1; i < position; i++) {
            before = before->next;
            remove = remove->next;
            after = after->next;
        }
        //remove somewhere in the middle
        object = remove->data;
        remove->data = nullptr;
        after->previous = before;
        before->next = after;
        remove->next = nullptr;
        remove->previous = nullptr;
        delete remove;
    }
    _size--;
	return object;
}
/**
 * Get
 * Gets the data at given position in the DoubleLinkedList
 * @param position of the data to be found
 * @return the data at given position if found, null otherwise
 */
Object *DoubleLinkedList::Get(size_t position) const {
    if(position >= _size){
        return nullptr;
    }
    if(position == 0){
        return _head->data;
    }
    else if(position == _size - 1){
        return _tail->data;
    }
    Node* temp = _head;
    for(size_t i = 0; i < position; i++){
        temp = temp->next;
    }
	return temp->data;
}
/**
 * ToString
 * Creates a string representation of the DoubleLinkedList.
 * @return a string representing the DoubleLinkedList
 */
string DoubleLinkedList::ToString() const {
    stringstream ss;
    ss << "{";
    Node* temp = _head;
    while(temp->next != nullptr){
        ss << temp->data->ToString() << ", ";
        temp = temp->next;
    }
    ss << temp->data->ToString() << "}";
	return ss.str();
}
/**
 * Clear
 * Deletes the whole DoubleLinkedList
 */
void DoubleLinkedList::Clear() {
    Node *temp = _head;
    while(_head != nullptr){
        _head = temp->next;
        delete temp->data;
        delete temp;
        temp = _head;
    }
    _head = nullptr;
    _tail = nullptr;
    _size = 0;
}

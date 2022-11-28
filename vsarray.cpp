//
// Created by Arias Arevalo, Carlos on 5/6/20.
//
/*
 * Title:		VSArray Implementation
 * Purpose:		Definition of methods of a VSArray class
 * Author:		Karena Qian, Carlos Arias
 * Date:		May 10, 2022
 */

#include "object.h"
#include "list.h"
#include "vsarray.h"

#include <string>
#include <sstream>
using std::string;
using std::stringstream;

/**
 * Constructor
 * Creates an empty VSArray with the given info
 * @param capacity
 * @param increasePercentage
 */
VSArray::VSArray(size_t capacity, double increasePercentage): List(), _capacity(capacity), _delta(increasePercentage){
    _data = new Object*[_capacity];
    for (size_t i = 0; i < _capacity; i++) {
        _data[i] = nullptr;
    }
}
/**
 * Copy constructor
 * Create a deep copy of another VSArray
 * @param other VSArray
 */
VSArray::VSArray(const VSArray& list): List(list), _capacity(list._capacity), _delta(list._delta){
    _size = list._size;
    _data = new Object*[_capacity];
    for (size_t i = 0; i < _size; i++) {
        _data[i] = list.Get(i)->Clone();
    }
    for (size_t i = _size; i < _capacity; i++){
        _data[i] = nullptr;
    }
}
/**
 * Destructor
 * Releases the memory used by the VSArray
 */
VSArray::~VSArray(){
    for(int i = 0; i < _size; i++){
        delete _data[i];
    }
    delete[] _data;
    _size = 0;
    _capacity = 0;
}
/**
 * Copy Assignment Operator
 * Creates a deep copy of another VSArray
 * @param rhs VSArray
 * @return this to follow chain assignment standard
 */
const VSArray& VSArray::operator=(const VSArray& rhs){
    if (&rhs == this){
        return *this;
    }
    if (_capacity != rhs._capacity){
        Clear();
        delete[] _data;
        _capacity = rhs._capacity;
        _data = new Object*[_capacity];
        for (size_t i = 0; i < _capacity; i++) {
            _data[i] = nullptr;
        }
    }
    for (size_t i = 0; i < rhs.Size(); i++) {
        _data[i] = rhs.Get(i)->Clone();
    }
    return *this;
}
/**
 * Insert
 * Insert the given element at given position in the VSArray
 * @param element to be inserted in the VSArray
 * @param position where the element is to be inserted
 * @return true, if the element is inserted successively, false otherwise
 */
bool VSArray::Insert(Object* element, size_t position){
    // Check if the position is valid
    if (position > _size) {
        return false;
    }
    // Check if there is enough space
    if (_capacity == _size) {
        Resize();
    }
    if (position < _size){
        for (size_t i = _size; i > position; i--){
            _data[i] = _data[i - 1];
        }
    }
    _data[position] = element;
    _size++;
    return true;
}
/**
 * IndexOf
 * Returns the index of given element in VSArray, if found
 * @param element to be found in the VSArray
 * @return the index of given element if found, -1 otherwise
 */
int VSArray::IndexOf(const Object* element)const{
    for (int i = 0; i < _size; i++) {
        if (_data[i]->Equals(*element)){
            return i;
        }
    }
    return -1;
}
/**
 * Remove
 * Remove an element at given position in the VSArray
 * @param position where an element is to be removed
 * @return the removed element's data if removed successfully, null otherwise
 */
Object* VSArray::Remove(size_t position){
    if (position >= _size){
        return nullptr;
    }
    Object* retVal = _data[position];
    for (size_t i = position; i < _size - 1; i++) {
        _data[i] = _data[i + 1];
    }
    _data[_size - 1] = nullptr;
    _size--;
    return retVal;
}
/**
 * Get
 * Gets the data at given position in the VSArray
 * @param position of the data to be found
 * @return the data at given position if found, null otherwise
 */
Object* VSArray::Get(size_t position)const{
    if (position >= _size) {
        return nullptr;
    }
    else {
        return _data[position];
    }
}
/**
 * ToString
 * Creates a string representation of the VSArray.
 * @return a string representing the VSArray
 */
string VSArray::ToString()const{
    stringstream retVal;
    retVal << "{";
    for (size_t i = 0; i < _size - 1; i++) {
        retVal << _data[i]->ToString() << ", ";
    }
    retVal << _data[_size - 1]->ToString() << "}";
    return retVal.str();
}
/**
 * Clear
 * Deletes the whole VSArray
 */
void VSArray::Clear(){
    for(int i = 0; i < _size; i++){
        delete _data[i];
        _data[i] = nullptr;
    }
    _size = 0;
    _capacity = 0;
}
/**
 * Resize
 * Increases the capacity of the VSArray
 */
void VSArray::Resize() {
    size_t newCapacity = _capacity + static_cast<size_t>(_capacity * _delta);
    size_t size = _size;
    Object** newData = new Object*[newCapacity];
    for (size_t i = 0; i < _capacity; i++) {
        newData[i] = _data[i]->Clone();
        delete _data[i];
    }
    for (size_t i = _capacity; i < newCapacity; i++) {
        newData[i] = nullptr;
    }
    delete[] _data;
    _data = newData;
    _capacity = newCapacity;
    _size = size;
}
/**
 * GetCapacity
 * Returns the capacity of the VSArray
 * @return _capacity of VSArray
 */
size_t VSArray::GetCapacity() const {
	return _capacity;
}

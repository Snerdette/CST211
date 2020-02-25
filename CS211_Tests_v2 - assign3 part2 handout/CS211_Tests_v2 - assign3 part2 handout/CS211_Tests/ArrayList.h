// ArrayList.h
// Pete Myers, OIT Winter 2020
// ArrayList implementation of the List data structure
//
// Handout Assignment 2 & 3
// By Kate LaFrance
//

#pragma once

#include "List.h"
#include <stddef.h>

template <class T> class ArrayList : public List<T>
{
private:
	T* contents;
	int capacity;	// How the Array is
	int count;		// how much of the Array is Used.


public:
	ArrayList()
	{
		capacity = 10;							// Default
		contents = new T[capacity];				// Memory for the initial capacity
		count = 0;								// Empty list to start
	}

	ArrayList(const ArrayList<T>& copyFrom) {

		// Copy the values from copyFrom to this new list
		capacity = copyFrom.capacity;
		contents = new T[capacity];
		count = copyFrom.count;

		// Deep copy the contents
		for (int i = 0; i < count; i++) {
			contents[i] = copyFrom.contents[i];
		}
	}

	void operator=(const ArrayList<T>& copyFrom) {

		// Nuke current contents if necessary
		if (capacity != copyFrom.capacity) {

			if (contents != nullptr) {
				delete[] contents;
			}

			capacity = copyFrom.capacity;
			contents = new T[capacity];
		}

		count = copyFrom.count;

		// Deep copy the contents from copyFrom to this new list
		for (int i = 0; i < count; i++) {
			contents[i] = copyFrom.contents[i];
		}
	}

	virtual int Count() const		// returns the number of items in the list
	{
		return count;
	}

	virtual void Insert(const T& item, int index)    // index from 0 to Count
	{

		ValidateInsertIndex(index);

		// Grow if needed, makes a hole
		Grow();

		for (int i = count; i > index; i--) {
			contents[i] = contents[i - 1];
		}

		contents[index] = item;
		count++;

	}

	virtual void Append(const T& item)      // add to end of list
	{
		// Grow if needed
		Grow();

		// Append
		contents[count] = item;
		count++;
	}

	virtual T Remove(int index)            // remove item at index
	{
		ValidateIndex(index);

		// Copied to return
		T temp = contents[index];

		// Copy over index of item to be removed, shift all
		for (int i = index; i < count - 1; i++) {
			contents[i] = contents[i + 1];
		}

		// Adjusting count -1
		count--;

		return temp;
	}

	virtual const T& Get(int index) const   // return item at index
	{
		ValidateIndex(index);
		return contents[index];
	}

	void Set(int index, const T value) {
		ValidateIndex(index);
		contents[index] = value;
	}


	class ArrayListIterator : public List<T>::ListIterator
	{
	private:
		ArrayList<T>* theList;
		int currentIndex;

	public:
		ArrayListIterator(ArrayList<T>* theList, int startAt) : theList(theList), currentIndex(startAt)
		{
		}

		virtual bool HasNext() const		// returns true if there is a next item
		{
			return currentIndex < theList->count;
		}

		virtual T& Next()					// returns next item and advances iterator toward end
		{
			if (HasNext()) {
				return theList->contents[currentIndex++];
			}
			else {
				throw "No Next Item for Iterator";
			}

		}

		virtual bool HasPrevious() const	// returns true if there is a previous item
		{
			return currentIndex > 0;
		}

		virtual T& Previous()				// returns previous item and advances iterator toward beginning
		{
			if (HasPrevious()) {
				return theList->contents[--currentIndex];
			}
			else {
				throw "No Previous Item for Iterator";
			}
		}

		virtual void Insert(const T& item)	// inserts item at current position, making room as needed
		{
			// Reusing the List Insert method
			return theList->Insert(item, currentIndex);
		}

		virtual T Remove()					// removes item at current position, contracting the list
		{
			// Reusing the List Remove method
			return theList->Remove(currentIndex);
		}

	};

	virtual List<T>::ListIterator* Begin()	// returns new iterator at beginning of list
	{
		// Create an Iterator that points to the first index
		return new ArrayListIterator(this, 0);
	}

	virtual List<T>::ListIterator* End()	// Returns new iterator at end of list
	{
		// Create an Iterator that points to the last index
		return new ArrayListIterator(this, count);
	}

private:

	virtual void Grow() {

		if (count >= capacity) {

			// New array with 2x capacity
			T* newContents = new T[2 * capacity];

			// Moving contents to bigger list
			for (int i = 0; i < capacity; i++) {
				newContents[i] = contents[i];
			}

			// deleting what contents is pointing to
			delete[] contents;

			// Moving pointer of newContents to the memory location of contents.
			contents = newContents;

			// Increasing new list's capacity
			capacity *= 2;

		}

	}

	// Make sure index is within the list or is the last
	void ValidateIndex(int index) const {
		if (index < 0 || index >= count) {
			throw "Index out of range (ValidateIndex)";
		}
	}

	// Make sure index is within the list
	void ValidateInsertIndex(int index) const {
		if (index < 0 || index > count) {
			throw "Index out of range (ValidateIndex)";
		}
	}

};

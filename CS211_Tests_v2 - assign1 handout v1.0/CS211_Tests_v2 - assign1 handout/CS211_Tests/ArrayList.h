// ArrayList.h
// Pete Myers, OIT Winter 2020
// ArrayList implementation of the List data structure
//
// Handout Assign1
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
		capacity = 10;				// Default
		contents = new T[capacity];	// Memory for the initial capacity
		count = 0;
	}

	virtual int Count() const		// returns the number of items in the list
	{
		// TODO
		throw "TODO";
	}

	virtual void Insert(const T & item, int index)    // index from 0 to Count
	{
		// TODO
		throw "TODO";
	}

	virtual void Append(const T & item)      // add to end of list
	{
		if (count < capacity) {
			contents[count] = item;
			count++;
		}
		else {
			// Extend Capacity
			// TODO: Double capacity;
		}
		
	}

	virtual T Remove(int index)            // remove item at index
	{
		// TODO
		throw "TODO";
	}

	virtual const T & Get(int index) const   // return item at index
	{
		if (index < count) {

		}
		else {
			// Outside!
			throw "Error in GET! Index out of range";
		}
		return contents[index];
	}


	class ArrayListIterator : public List<T>::ListIterator
	{
	private:
		ArrayList<T>* theList;
		int currentIndex;

	public:
		ArrayListIterator(ArrayList<T> * theList, int startAt) : theList(theList), currentIndex(startAt)
		{
		}

		virtual bool HasNext() const    // returns true if there is a next item
		{
			return currentIndex < theList->count;
		}

		virtual T & Next()              // returns next item and advances iterator toward end
		{
			// TODO
			throw "TODO";
		}

		virtual bool HasPrevious() const// returns true if there is a previous item
		{
			// TODO
			throw "TODO";
		}

		virtual T & Previous()          // returns previous item and advances iterator toward beginning
		{
			// TODO
			throw "TODO";
		}

		virtual void Insert(const T & item)  // inserts item at current position, making room as needed
		{
			// TODO
			throw "TODO";
		}

		virtual T Remove()        // removes item at current position, contracting the list
		{
			// TODO
			throw "TODO";
		}

	};

	virtual List<T>::ListIterator * Begin()  // returns new iterator at beginning of list
	{
		// Create an Iterator that points to the first point at the
		ArrayListIterator iter = new ArrayListIterator(this, 0);
		
		return iter;
	}

	virtual List<T>::ListIterator * End()    // returns new iterator past end of list
	{
		// TODO
		throw "TODO";
	}

};

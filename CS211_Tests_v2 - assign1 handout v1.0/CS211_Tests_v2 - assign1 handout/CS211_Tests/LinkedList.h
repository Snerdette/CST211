// LinkedList.h
// Pete Myers, OIT Winter 2020
// Double-Linked List implementation of the List data structure
//
// Handout Assign1
//

#pragma once

#include "List.h"

template <class T> class LinkedList : public List<T>
{
private:
	class Node
	{
	public:
		// TODO
	};

	// TODO

public:
	LinkedList()
	{
		// TODO
		throw "TODO";
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
		// TODO
		throw "TODO";
	}

	virtual T Remove(int index)            // remove item at index
	{
		// TODO
		throw "TODO";
	}

	virtual const T & Get(int index) const   // return item at index
	{
		// TODO
		throw "TODO";
	}


	class LinkedListIterator : public List<T>::ListIterator
	{
	private:
		// TODO

	public:
		LinkedListIterator(LinkedList * theList, Node * startAt)
		{
			// TODO
			throw "TODO";
		}

		virtual bool HasNext() const    // returns true if there is a next item
		{
			// TODO
			throw "TODO";
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

		const T & Get() const
		{
			// TODO
			throw "TODO";
		}
	};

	virtual List<T>::ListIterator * Begin()  // returns new iterator at beginning of list
	{
		// TODO
		throw "TODO";
	}

	virtual List<T>::ListIterator * End()    // returns new iterator past end of list
	{
		// TODO
		throw "TODO";
	}
};


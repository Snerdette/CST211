// OrderedList.h
// Pete Myers, OIT Winter 2020
// Interface for OrderedList data structure

#pragma once

template <class T> class OrderedList
{	
public:
	virtual int Count() const = 0; // return the number of items in the list
	virtual void Add(const T & item) = 0;  // add new item into proper location in list
	virtual void Remove(const T & item) = 0;  // remove item from list, if it exists

	class OrderedListIterator
	{
	public:
		virtual bool HasNext() const = 0; // return true if there is a next item
		virtual T & Next() = 0;   // return next item and advance iterator toward end
	};

	virtual OrderedListIterator * Begin() = 0; // return new iterator at beginning of list
	virtual OrderedListIterator * Find(const T & target) = 0; // return new iterator at target's location in the list, or nullptr if not found
};


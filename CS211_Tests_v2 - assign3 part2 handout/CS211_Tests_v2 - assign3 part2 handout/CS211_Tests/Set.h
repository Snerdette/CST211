// Set.h
// Pete Myers, OIT Winter 2020
// Abstract interface for the Set data structure

#pragma once

template <class T> class SetIterator
{
public:
	virtual bool HasNext() const = 0;	// returns true if there is a next item
	virtual T Next() = 0;				// returns next item and advances iterator toward end
};

template <class T> class Set
{
public:
	virtual int Count() const = 0;			// return the number of items in the set
	virtual void Add(const T& item) = 0;	// add item to the set, no action if already there
	virtual void Remove(const T& item) = 0;	// remove item from the set
	virtual bool Contains(const T& item) const = 0;	// return true if item is in the set
	virtual SetIterator<T>* Iterate() = 0;		// returns new iterator for the set
};

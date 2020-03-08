// HashSet.h
// Pete Myers, OIT Winter 2020
// Hash table implementation of the Set data structure
//
// By Kate LaFrance
// Handout Assignment 3 part 2
//

#pragma once

#include "Set.h"
#include "Hash.h"
#include "Dictionary.h"
#include "HashDictionary.h"


template <class T> class HashSet : public Set<T>
{
private:
	HashDictionary<T, bool> dictionary;
public:
	HashSet(Hasher<T>* hasher): dictionary(hasher)
	{
	}

	virtual int Count() const
	{
		// Call HashDictionary class's Count() and return the number of items in the set
		return dictionary.Count();
	}

	virtual void Add(const T& item)
	{
		// Call HashDictionary class's Add() and add the item to the set
		// No action if already there
		dictionary.Add(item, true);
	}

	virtual void Remove(const T& item)
	{
		// Call HashDictionary class's Remove() to remove the item from the set
		dictionary.Remove(item);
	}

	virtual bool Contains(const T& item) const
	{
		// Call HashDictionary class's Contains() and return true if item is in the set
		return dictionary.Contains(item);
	}

	virtual SetIterator<T>* Iterate()
	{
		// Returns a new iterator for the set
		return new HashSetIterator(this);
	}

private:
	class HashSetIterator : public SetIterator<T>
	{
	private:
		HashSet<T>* theSet;
		DictionaryIterator<T, bool>* iter;

	public:
		HashSetIterator(HashSet<T>* theSet) : theSet(theSet)
		{
			iter = theSet->dictionary.Iterate();
		}

		virtual bool HasNext() const
		{
			// Calls the DictionaryIterator HasNext() and returns true if there is a next item
			return iter->HasNext();
		}

		virtual T Next()
		{
			// Calls DictionaryIterator's Next(), returns the next item, and advances iterator toward end
			return iter->Next().key;
		}
	};
};


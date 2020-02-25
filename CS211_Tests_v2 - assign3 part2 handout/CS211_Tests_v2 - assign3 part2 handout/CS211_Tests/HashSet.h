// HashSet.h
// Pete Myers, OIT Winter 2020
// Hash table implementation of the Set data structure
//
// Handout Assign3 part 2
//

#pragma once

#include "Set.h"
#include "Hash.h"
#include "Dictionary.h"
#include "HashDictionary.h"


template <class T> class HashSet : public Set<T>
{
private:

public:
	HashSet(Hasher<T>* hasher)
	{
		throw "TODO: HashSet::ctor()";
	}

	virtual int Count() const
	{
		// return the number of items in the set
		throw "TODO: HashSet::Count()";
	}

	virtual void Add(const T& item)
	{
		// add item to the set, no action if already there
		throw "TODO: HashSet::Add()";
	}

	virtual void Remove(const T& item)
	{
		// remove item from the set
		throw "TODO: HashSet::Remove()";
	}

	virtual bool Contains(const T& item) const
	{
		// return true if item is in the set
		throw "TODO: HashSet::Contains()";
	}

	virtual SetIterator<T>* Iterate()
	{
		// returns new iterator for the set
		throw "TODO: HashSet::Iterate()";
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
			throw "TODO: HashSetIterator::ctor()";
		}

		virtual bool HasNext() const
		{
			// returns true if there is a next item
			throw "TODO: HashSetIterator::HasNext()";
		}

		virtual T Next()
		{
			// returns next item and advances iterator toward end
			throw "TODO: HashSetIterator::Next()";
		}
	};
};


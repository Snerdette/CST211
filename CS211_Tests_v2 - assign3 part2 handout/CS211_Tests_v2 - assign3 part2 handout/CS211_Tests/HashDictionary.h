// HashDictionary.h
// Pete Myers, OIT Winter 2020
// Hash table implementation of the Dictionary data structure
//
// Handout Assign3 part 2
//

#pragma once

#include "Dictionary.h"
#include "Hash.h"


template <class K, class V> class HashDictionary : public Dictionary<K,V>
{
private:
	Hasher<K> * hasher;

public:
	HashDictionary(Hasher<K> * hasher) : hasher(hasher)
	{
		throw "TODO: HashDictionary::ctor()";
	}

	virtual int Count() const
	{
		// return the number of items in the dictionary
		throw "TODO: HashDictionary::Count()";
	}

	virtual void Add(const K& key, const V& value)
	{
		// add key/value pair to the dictionary, no action if already there
		int hc = hasher->Hash(key);
		throw "TODO: HashDictionary::Add()";
	}

	virtual void Remove(const K& key)
	{
		// remove key from the dictionary, along with its value
		throw "TODO: HashDictionary::Remove()";
	}

	virtual bool Contains(const K& key) const
	{
		// return true if key is in the dictionary
		throw "TODO: HashDictionary::Contains()";
	}

	virtual V& Get(const K& key) const
	{
		// return the value for key
		throw "TODO: HashDictionary::Get()";
	}

	virtual DictionaryIterator<K, V>* Iterate()
	{
		// returns new iterator for the dictionary
		throw "TODO: HashDictionary::Iterate()";
	}

private:
	class HashDictionaryIterator : public DictionaryIterator<K, V>
	{
	public:
		virtual bool HasNext() const
		{
			// returns true if there is a next item
			throw "TODO: HashDictionaryIterator::HasNext()";
		}

		virtual Pair<K, V> Next()
		{
			// returns next item and advances iterator toward end
			throw "TODO: HashDictionaryIterator::Next()";
		}
	};
};

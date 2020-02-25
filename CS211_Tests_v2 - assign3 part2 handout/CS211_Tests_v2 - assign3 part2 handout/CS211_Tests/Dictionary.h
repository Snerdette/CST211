// Dictionary.h
// Pete Myers, OIT Winter 2020
// Abstract interface for the Dictionary data structure

#pragma once

template <class K, class V> class Pair
{
public:
	K key;
	V value;
};

template <class K, class V> class DictionaryIterator
{
public:
	virtual bool HasNext() const = 0;	// returns true if there is a next item
	virtual Pair<K, V> Next() = 0;		// returns next item and advances iterator toward end
};

template <class K, class V> class Dictionary
{
public:
	virtual int Count() const = 0;						// return the number of items in the dictionary
	virtual void Add(const K& key, const V& value) = 0;	// add key/value pair to the dictionary, no action if already there
	virtual void Remove(const K& key) = 0;				// remove key from the dictionary, along with its value
	virtual bool Contains(const K& key) const = 0;		// return true if key is in the dictionary
	virtual V& Get(const K& key) const = 0;				// return the value for key
	virtual DictionaryIterator<K,V>* Iterate() = 0;		// returns new iterator for the dictionary
};

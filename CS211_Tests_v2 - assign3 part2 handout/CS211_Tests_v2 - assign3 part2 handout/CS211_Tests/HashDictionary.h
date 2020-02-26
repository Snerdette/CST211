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

	class HashTable
	{
	public:
		HashTable(int capacity) {};
		void Add(const K& key, const V& value) {};
		bool Contains(const K& key) const { return false; };
		Pair<K, V>* operator[](int i) { return nullptr; };
	};

	Hasher<K> * hasher;
	int count;
	int capacity;
	//Pair<K, V>** theHashTable;		// An array of pointers to Pair<K,V>
	HashTable* theHashTable;

public:
	HashDictionary(Hasher<K>* hasher) : hasher(hasher)
	{
		count = 0;
		capacity = 10;
		//theHashTable = new Pair<K, V> * [capacity] {nullptr};	// Initializes the hashtable to be empty		
		theHashTable = new HashTable(capacity);
	}

	virtual int Count() const
	{
		// return the number of items in the dictionary
		return count;
	}

	virtual void Add(const K& key, const V& value)
	{

		// 1. Check for duplicate keys, stop if already present
		if (!theHashTable->Contains(key)) {
			
			// 2. Grow if necessary
			if (count == capacity) {
				// Grow the table
				HashTable* newHashTable = new HashTable(capacity * 2);
				for (int i = 0; i < capacity; i++)
				{
					if ((*theHashTable)[i] != nullptr) {
						newHashTable->Add((*theHashTable)[i]->key, (*theHashTable)[i]->value);
					}
					delete theHashTable;
					theHashTable = newHashTable;
					capacity *= 2;
				}

			}

			// 3. Add the new key/value pair
			theHashTable->Add(key, value);
			count++;
		}
		// add key/value pair to the dictionary, no action if already there

		// Check for duplicate key.
		//int hc = hasher->Hash(key) % capacity;
		//if (theHashTable[hc] == nullptr || theHashTable[hc]->key != key) {

		//	// Know when to grow!
		//	if (count == capacity) {

		//		// Save the old for a moment
		//		int oldCount = count;
		//		int oldCapacity = capacity;
		//		Pair<K, V>** oldHashTable = theHashTable;

		//		// Grow the hash table
		//		count = 0;
		//		capacity *= 2;
		//		theHashTable = new Pair<K, V> * [capacity] { nullptr };

		//		for (int i = 0; i < length; i++)
		//			Add(oldHashTable[i].key, oldHashTable[i].value);

		//		// Delete oldHashTable
		//		delete[] oldHashTable;
		//	}
		//}

		//

		//

		//// Store key/value at hc index.
		//theHashTable[hc] = new Pair<K, V>{ key, value };

		//// Increment the count
		//count++;
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

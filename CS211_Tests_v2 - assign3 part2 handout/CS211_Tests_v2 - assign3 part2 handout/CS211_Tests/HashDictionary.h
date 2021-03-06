// HashDictionary.h
// Pete Myers, OIT Winter 2020
// Hash table implementation of the Dictionary data structure
//
// By Kate LaFrance
// Handout Assignment 3 part 2
//

#pragma once

#include "Dictionary.h"
#include "Hash.h"


template <class K, class V> class HashDictionary : public Dictionary<K,V>
{
private:

	class HashTable
	{
	private: 
		Hasher<K>* hasher;
		int count;
		int capacity;
		Pair<K, V>** contents;		// an array of pointers to Pair<K, V>
	public:

		HashTable(Hasher<K>* hasher, int capacity): hasher(hasher), capacity(capacity), count(0)
		{
			// Array of pair pointers initialized to nullptr
			contents = new Pair<K, V> * [capacity] { nullptr };
		};

		int Capacity() { return capacity; }
		int Count() { return count; }


		void Add(const K& key, const V& value) 
		{
			// Check for capacity
			if (count == capacity) {
				throw "No more room in the hash table!!";
			}

			// Check for duplicate key.
			int hc = hasher->Hash(key) % capacity;

			// Find empty space in hash table
			if (contents[hc] != nullptr) 
			{
				// Linerar probe to find an available cell.

				while (contents[hc] != nullptr) {
					hc = (hc + 1) % capacity;		// Loop around if reach the end.
				}
			}

			// Store the key/value at the hc index.
			contents[hc] = new Pair<K, V>{ key, value };

			// increment count
			count++;
		};

		void Remove(const K& key)
		{
			// Get hash code for key.
			int hc = hasher->Hash(key) % capacity;

			// Store in temp for do whiles' termination value.
			int tryHc = hc;

			do {

				// Check if there's nothing there
				if (contents[tryHc] == nullptr)
					throw "This key does not exsist!";

				// check if key is actually found
				if (contents[tryHc]->key == key) {
					
					// Nuke value
					contents[tryHc] = nullptr;

					// Decrement the count
					count--;

					// End the search
					return;
				}

				// Probe forward!
				tryHc = (tryHc + 1) % capacity;

			} while (tryHc != hc);

			// If not found at all
			throw "Key does not exsist!";
		}

		Pair<K, V>* Get(const K& key) const
		{
			// Get hash code for key.
			int hc = hasher->Hash(key) % capacity;

			// Store in temp for do whiles' termination value.
			int tryHc = hc;

			do {

				// Check if there's nothing there
				if (contents[tryHc] == nullptr)
					return nullptr;

				// check if key is actually found
				if (contents[tryHc]->key == key)
					return contents[tryHc];


				// Probe forward!
				tryHc = (tryHc + 1) % capacity;

			} while (tryHc != hc);

			// looped through all and key not found!
			return nullptr;
		}

		Pair<K, V>* GetPairAt(int i) 
		{ 
			return contents[i]; 
		};
	};

	Hasher<K> * hasher;
	//Pair<K, V>** theHashTable;		// An array of pointers to Pair<K,V>
	HashTable* theHashTable;
	int count;
	int capacity;

public:
	HashDictionary(Hasher<K>* hasher) : hasher(hasher)
	{
		//theHashTable = new Pair<K, V> * [capacity] {nullptr};	// Initializes the hashtable to be empty		
		theHashTable = new HashTable(hasher, 10);
	}


	virtual int Count() const
	{
		// return the number of items in the dictionary
		return theHashTable->Count();
	}

	virtual void Add(const K& key, const V& value)
	{

		// 1. Check for duplicate keys, stop if already present
		if (!theHashTable->Get(key)) {
			
			// 2. Grow if necessary
			if (theHashTable->Count() == theHashTable->Capacity()) {
				// Grow the table
				HashTable* newHashTable = new HashTable(hasher, theHashTable->Capacity() * 2);
				for (int i = 0; i < theHashTable->Capacity(); i++)
				{
					newHashTable->Add(theHashTable->GetPairAt(i)->key, theHashTable->GetPairAt(i)->value);
				}

				// out with old, in with new
				delete theHashTable;
				theHashTable = newHashTable;

			}

			// 3. Add the new key/value pair
			theHashTable->Add(key, value);
		}	
	}

	virtual void Remove(const K& key)
	{
		// Call hashtable class's remove function
		theHashTable->Remove(key);
	}

	virtual bool Contains(const K& key) const
	{
		// return true if key is in the dictionary
		return theHashTable->Get(key) != nullptr;
	}

	virtual V& Get(const K& key) const
	{
		Pair<K, V>* pair = theHashTable->Get(key);

		if(pair == nullptr)
			throw "Get(key) not found";

		// return the value for key
		return pair->value;
		
		
	}

	virtual DictionaryIterator<K, V>* Iterate()
	{
		// returns new iterator for the dictionary
		return new HashDictionaryIterator(this);
	}

private:
	class HashDictionaryIterator : public DictionaryIterator<K, V>
	{

	private:
		HashDictionary* theDictionary;
		int currentIndex;
	public:

		HashDictionaryIterator(HashDictionary * theDictionary): theDictionary(theDictionary)
		{
			// Start at "first" pair in hash table
			currentIndex = 0;

			// Find the first non-empty cell in the hash table
			while (currentIndex < theDictionary->theHashTable->Capacity() &&
				theDictionary->theHashTable->GetPairAt(currentIndex) == nullptr)
			{
				currentIndex++;
			}
		}

		virtual bool HasNext() const
		{
			// returns true if there is a next item
			// Returns true is the index is within the capacity
			// and there is a pair at the current location
			return (currentIndex < theDictionary->theHashTable->Capacity() &&
				theDictionary->theHashTable->GetPairAt(currentIndex) != nullptr);
			
		}

		virtual Pair<K, V> Next()
		{
			// Get the pair at the current index
			Pair<K, V>* pair = theDictionary->theHashTable->GetPairAt(currentIndex);

			// Check if nullptr, if so throw exception
			if (pair == nullptr)
				throw "No next pair for dictionary!";

			// Increment index to the "next" index
			currentIndex++;

			// Advance iterator to the next non-empty cell in the hash table
			while (currentIndex < theDictionary->theHashTable->Capacity() &&
				theDictionary->theHashTable->GetPairAt(currentIndex) == nullptr)
			{
				currentIndex++;
			}

			// Return the pair
			return *pair;
		}
	};

	
};

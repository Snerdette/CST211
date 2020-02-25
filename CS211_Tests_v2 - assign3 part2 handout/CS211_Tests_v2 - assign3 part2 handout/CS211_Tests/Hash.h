// Hash.h
// Pete Myers, OIT Winter 2020
// Interface for hashing data to create hash codes
//
// Handout Assign3 part 2
//

#pragma once

template <class K> class Hasher
{
public:
	virtual int Hash(const K& key) const = 0;
};

// BinaryTreeList.h
// Pete Myers, OIT Winter 2020
// Implementation of a OrderedList data structure using a binary search tree
//
// Handout Assign2
//

#pragma once

#include "OrderedList.h"
#include "ArrayListStack.h"


template <class T> class BinaryTreeList : public OrderedList<T>
{
private:
	class Node
	{
	public:
		Node(const T& item)
		{
			// TODO
		}
		
		// TODO
	};

	// TODO

public:
	BinaryTreeList()
	{
		// TODO
	}

	virtual int Count() const  // return the number of items in the list
	{
		// TODO
		throw "TODO";
	}

	virtual void Add(const T & item)  // add new item into proper location in list
	{
		// TODO
		throw "TODO";
	}

	virtual void Remove(const T & item)  // remove item from list, if it exists
	{
		// TODO
		throw "TODO";
	}

private:
	class BinaryTreeListIterator : public OrderedList<T>::OrderedListIterator
	{
	private:
		// TODO

	public:
		BinaryTreeListIterator(BinaryTreeList * list)
		{
			// start at root of tree and then to the smallest node in the tree
			// TODO
		}

		BinaryTreeListIterator(BinaryTreeList* list, Node* startAt, const ArrayListStack<Node*>& path)
		{
			// start at specific node, including path to node
			// TODO
		}

		virtual bool HasNext() const    // return true if there is a next item
		{
			// TODO
			throw "TODO";
		}

		virtual T & Next()   // return next item and advance iterator toward end
		{
			// TODO
			throw "TODO";
		}
	};

public:
	virtual OrderedList<T>::OrderedListIterator * Begin() // return new iterator at beginning of list
	{
		// TODO
		throw "TODO";
	}

	virtual OrderedList<T>::OrderedListIterator * Find(const T & target) // return new iterator at target's location in the list, or nullptr if not found
	{
		// TODO
		throw "TODO";
	}

private:
	// TODO
};


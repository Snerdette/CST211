// BinaryTreeList.h
// Pete Myers, OIT Winter 2020
// Implementation of a OrderedList data structure using a binary search tree
//
// Handout Assignment 2
// By Kate LaFrance
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
		Node(const T& item): item(item), left(nullptr), right(nullptr)
		{
			
		}
		
		T item;
		Node* left;
		Node* right;
	};

	Node* root;
	int count;

public:
	BinaryTreeList(): root(nullptr), count(0)
	{
		// Initialize to an empty list
	}

	virtual int Count() const  // return the number of items in the list
	{
		return count;
	}

	virtual void Add(const T & item)  // add new item into proper location in list
	{
		// For an empty tree, add node in proper place.
		if (root == nullptr) {
			root = new Node(item);
		}
		else {
			// Tree already has stuff in it
			// Call recursive add function containing nullptr checks
			RecursiveAdd(root, item);
		}
		count++;
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
	
	void RecursiveAdd(Node* node, const T& item) {
	
		if (item < node->item) {
			// Go left
			if (node->left == nullptr) {
				// If no left child, add new node to parent's left
				node->left = new Node(item);
			}
			else {
				// Have a left child, so recurse left
				RecursiveAdd(node->left, item);
			}	
		}
		else {
			// Go right
			if (node->right == nullptr) {
				// No right child, add new node to parent's right
				node->right = new Node(item);
			}
			else {
				// Add the new node to it's parent's right
				RecursiveAdd(node->right, item);
			}
		}
	}
};


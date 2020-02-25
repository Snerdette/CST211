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
		Node(const T& item) : item(item), left(nullptr), right(nullptr) {	}

		T item;
		Node* left;
		Node* right;
	};

	Node* root;
	int count;

public:
	BinaryTreeList() : root(nullptr), count(0)
	{
		// Initialize to an empty list
	}

	virtual int Count() const  // return the number of items in the list
	{
		return count;
	}

	virtual void Add(const T& item)  // add new item into proper location in list
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

	virtual void Remove(const T& item)  // remove item from list, if it exists
	{
		ArrayListStack<Node*> path;
		Node* target_node = RecursiveFind(root, item, path);

		// If empty node
		if (target_node == nullptr) {
			throw "Can't remove node we can't find!";
		}

		// If target_node has no children...
		if (target_node->left == nullptr && target_node->right == nullptr)
		{
			// Just nuke the target node
			ReplaceNode(target_node, nullptr, path);
		}
		// else if target_node has 2 children
		else if (target_node->left != nullptr && target_node->right != nullptr)
		{
			// Find the next_larger node from the target_node
			// Go down to the right once and all the way to the left
			// Keeping track of the next_larger node's parent aong the way
			Node* next_largerParent = target_node;
			Node* next_larger = target_node->right;

			while (next_larger->left != nullptr) {
				next_largerParent = next_larger;
				next_larger = next_larger->left;
			}

			// If next_larger has a right child
			if (next_larger->right != nullptr) {
				// Replace next_larger w/next_larger->right
				if (next_largerParent->right == next_larger) {
					next_largerParent->right = next_larger->right;
				}
				else {
					next_largerParent->left = next_larger->right;
				}
			}

			// Replace target_node with next larger
			ReplaceNode(target_node, next_larger, path);
		}
		// else if target_node has 1 child
		else
		{
			// Get target_node's parent and promote our child
			Node* child = target_node->left != nullptr ? target_node->left : target_node->right;
			ReplaceNode(target_node, child, path);
		}

		// Nuke the target_node!
		delete target_node;
		count--;
	}

private:
	class BinaryTreeListIterator : public OrderedList<T>::OrderedListIterator
	{
	private:
		BinaryTreeList* theList;
		Node* currentNode;
		ArrayListStack<Node*> path;

	public:
		BinaryTreeListIterator(BinaryTreeList* list) : theList(list)
		{
			// start at root of tree and then to the smallest node in the tree
			currentNode = theList->root;
			while (currentNode->left != nullptr)
			{
				path.Push(currentNode);
				currentNode = currentNode->left;
			}
		}

		BinaryTreeListIterator(BinaryTreeList* list, Node* startAt, const ArrayListStack<Node*>& path) :
			theList(list), currentNode(startAt), path(path)
		{
			// start at specific node, including path to node
			// TODO
		}

		virtual bool HasNext() const    // return true if there is a next item
		{
			return currentNode != nullptr;
		}

		virtual T& Next()   // return next item and advance iterator toward end
		{
			if (!HasNext()) {
				throw "No next item for iterator!!";
			}

			// Return current Item.
			T returnThis = currentNode->item;

			// Advance the iterator to the next item
			if (currentNode->right != nullptr) {
				// Go down to the right once and all the way to the left.
				path.Push(currentNode);
				currentNode = currentNode->right;
				while (currentNode->left != nullptr) {
					path.Push(currentNode);
					currentNode = currentNode->left;
				}
			}
			else {
				// While we have a parent that is smaller, keep moving up to the parent
				// If we have run out of ancestors and have not found a larger item, then we're done.
				Node* parent = path.Count() > 0 ? path.Pop() : nullptr;
				while (parent != nullptr && parent->item < currentNode->item)
				{
					parent = path.Count() > 0 ? path.Pop() : nullptr;
				}

				currentNode = parent;
			}

			return returnThis;
		}
	};

public:
	virtual OrderedList<T>::OrderedListIterator* Begin() // return new iterator at beginning of list
	{
		return new BinaryTreeListIterator(this);
	}

	virtual OrderedList<T>::OrderedListIterator* Find(const T& target) // return new iterator at target's location in the list, or nullptr if not found
	{
		// Find target in list and get it's node and path from that to root.
		ArrayListStack<Node*> path;
		Node* node = RecursiveFind(root, target, path);

		// Reutn new binaryTreeListIterator, starting at that node
		if (node != nullptr) {
			return new BinaryTreeListIterator(this, node, path);
		}

		return nullptr;
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

	Node* RecursiveFind(Node* node, const T& target, ArrayListStack<Node*>& path) {
		// Base cases
		if (node == nullptr) {
			return nullptr;
		}
		if (node->item == target) {
			return node;
		}

		// Recursive case
		path.Push(node);
		if (target < node->item) {
			return RecursiveFind(node->left, target, path);
		}
		else {
			return RecursiveFind(node->right, target, path);
		}
	}

	void ReplaceNode(Node* replaceThis, Node* withThis, ArrayListStack<Node*>& path)
	{
		// Just nuke the target node
		if (path.Count() > 0)
		{
			// If replaceThis(AKA target_node) has a parent
			Node* parent = path.Pop();
			if (parent->left == replaceThis) {
				parent->left = withThis;
			}
			else {
				parent->right = withThis;
			}
		}
		else {
			// If target_node is an orphan (is root)
			root = withThis;
		}

		// Update withThis's children, to inherit replaceThis's children
		// withThis->left

		// Update withThis's children
		if (withThis != nullptr)
		{
			if (withThis != replaceThis->left) {
				withThis->left = replaceThis->left;
			}
			if (withThis != replaceThis->right) {
				withThis->right = replaceThis->right;
			}
		}
	}
};

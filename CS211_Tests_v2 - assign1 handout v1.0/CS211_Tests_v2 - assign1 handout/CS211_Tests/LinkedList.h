// LinkedList.h
// Pete Myers, OIT Winter 2020
// Double-Linked List implementation of the List data structure
//
// Handout Assignment 1
// Modified By Kate LaFrance
// CST 211 Data Structures

#pragma once

#include "List.h"

template <class T> class LinkedList : public List<T>
{
private:
	class Node
	{
	public:
		T item;
		Node* next;
		Node* prev;
		Node(const T & item, Node * next, Node * prev) : 
			item(item), next(next), prev(prev) {
		}
	};

	Node* head;
	Node* tail;
	int count;

public:
	LinkedList()
	{
		head = nullptr;
		tail = nullptr;
		count = 0;
	}

	virtual int Count() const		// Returns the number of items in the list
	{
		return count;
	}

	virtual void Insert(const T & item, int index)    // index from 0 to Count
	{
		ValidateInsertIndex(index);

		// Find a pointer to the insertion point and the previous node.
		Node* insertHere = head;
		Node* prevOne = nullptr;

		for (int i = 0; i < index; i++) {
			prevOne = insertHere;
			insertHere = insertHere->next;
		}

		InsertNode(item, insertHere, prevOne);
		
	}

	virtual void Append(const T & item)      // Add to end of list
	{
		// Create a new node to hold the item
		Node* newNode = new Node(item, nullptr, tail);

		// Append the new node
		if (head == nullptr) {
			
			// Empty list
			head = newNode;
		}
		else {
			// Not empty list
			tail->next = newNode;			
		}

		// Move tail and increment count
		tail = newNode;
		count++;
	}

	virtual T Remove(int index)            // Remove item at index
	{
		ValidateIndex(index);

		// Find a pointer to the new node so it may be removed.
		Node* nukeThis = head;
		for (int i = 0; i < index; i++)
		{
			nukeThis = nukeThis->next;
		}
		return RemoveNode(nukeThis);
	}

	virtual const T & Get(int index) const   // Return item at index
	{
		ValidateIndex(index);

		// Walks forward to find the next item at the index
		Node* n = head;
		for (int i = 0; i < index; i++) {
			n = n->next;
		}

		return n->item;
	}


	class LinkedListIterator : public List<T>::ListIterator
	{
	private:
		LinkedList * theList;
		Node * currentNode;
	public:
		LinkedListIterator(LinkedList * theList, Node * startAt) : 
			theList(theList), currentNode(startAt){}

		virtual bool HasNext() const    // Returns true if there is a next item
		{
			return currentNode != nullptr;		
		}

		virtual T & Next()              // Returns next item and advances iterator toward end
		{
			if (HasNext()) {
				T& returnThis = currentNode->item;
				currentNode = currentNode->next;
				return returnThis;
			}
			throw "No next node for iterator!(LinkedListIter)";		
		}

		virtual bool HasPrevious() const		// Returns true if there is a previous item
		{
			// Two cases:
				// If there is a currentNode, then we check if it's prev.
				// If there is no currentNode, then we're off the end of theList, and we check the tail.
			return currentNode == nullptr ? theList->tail != nullptr : currentNode->prev != nullptr;
		}

		virtual T & Previous()          // Returns previous item and advances iterator toward beginning
		{
			if (HasPrevious()) {
				// Move the iterator back towards the beginning
				currentNode = currentNode == nullptr ? currentNode = theList->tail : currentNode->prev;

				// Returns the item at the currentNode.
				return currentNode->item;
			}
			throw "No previous item for the iterator! (LLI-Previous())";
		}

		virtual void Insert(const T & item)  // Inserts item at current position, making room as needed
		{
			// Insert the item in a new node at the currentNode location
			theList->InsertNode(item, currentNode, currentNode == nullptr ? theList->tail : currentNode->prev);

			// Update currentNode to point to the newly created node.
			currentNode = currentNode == nullptr ? theList->tail : currentNode->prev;
		}

		virtual T Remove()        // Removes item at current position, contracting the list
		{
			if (currentNode == nullptr) 
				throw "Cannot remove past end of list";
			

			Node* nukeThis = currentNode;
			currentNode = currentNode->next;		// Advances the current pointer
			return theList->RemoveNode(nukeThis);
		}

		const T & Get() const		// Returns the current node if it's not empty
		{
			if (currentNode != nullptr)
			{
				return currentNode->item;
			}
			else {
				throw "No current item for iterators (Get)180";
			}		
		}
	};

	virtual List<T>::ListIterator * Begin()  // Returns new iterator at beginning of list
	{
		return new LinkedListIterator(this, head);
	}

	virtual List<T>::ListIterator * End()    // Returns new iterator past end of list
	{
		return new LinkedListIterator(this, nullptr);
	}

	// Make sure index is within the list or is the last
	void ValidateIndex(int index) const {
		if (index < 0 || index >= count) {
			throw "Index out of range (ValidateIndex)";
		}
	}

	// Make sure index is within the list
	void ValidateInsertIndex(int index) const {
		if (index < 0 || index > count) {
			throw "Index out of range (ValidateIndex)";
		}
	}

	T RemoveNode(Node* nukeThis) {

		Node* nextOne = nukeThis->next;
		Node* prevOne = nukeThis->prev;

		// set prevNode->next to nextOne
		if (prevOne == nullptr)
		{
			head = nextOne;		// deleting first item
		}
		else {
			prevOne->next = nextOne;
		}

		// set nextOne->prev to prevOne
		if (nextOne == nullptr)
		{
			tail = prevOne;		// deleting the last item
		}
		else {
			nextOne->prev = prevOne;
		}

		// Nuke it!
		T returnThis = nukeThis->item;
		delete nukeThis;
		count--;

		return returnThis;

	}

	void InsertNode(const T & item, Node * insertHere, Node * prevOne) {
		
		// Create new node for the item
		Node* newNode = new Node(item, insertHere, prevOne);


		// prevOne->next = newNode
		if (prevOne == nullptr) {
			head = newNode;
		}
		else {
			prevOne->next = newNode;
		}

		if (insertHere == nullptr) {
			tail = newNode;
		}
		else {
			insertHere->prev = newNode;
		}

		count++;
	}
};


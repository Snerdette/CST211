// LinkedList.h
// Pete Myers, OIT Winter 2020
// Double-Linked List implementation of the List data structure
//
// Handout Assign1
//

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
			item(item), next(next), prev(prev) {}
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

	virtual int Count() const		// returns the number of items in the list
	{
		return count;
	}

	virtual void Insert(const T & item, int index)    // index from 0 to Count
	{
		ValidateInsertIndex(index);

		Node * newNode = new Node(item, nullptr, nullptr);

		
		Node* insertHere = head;
		Node* prevOne = nullptr;
		for (int i = 0; i < index; i++) {
			prevOne = insertHere;
			insertHere = insertHere->next;
		}

		newNode->next = insertHere;
		newNode->prev = prevOne;

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

	virtual void Append(const T & item)      // add to end of list
	{
		Node* newNode = new Node(item, nullptr, tail);

		if (head == nullptr) {
			// Empty list
			head = newNode;
		}
		else {
			// !Empty list
			tail->next = newNode;			
		}

		// Move tail and increment count
		newNode->prev = tail;
		tail = newNode;
		count++;
	}

	virtual T Remove(int index)            // remove item at index
	{
		Node* nukeThis = head;
		for (int i = 0; i < index; i++)
		{
			nukeThis = nukeThis->next;
		}
		return RemoveNode(nukeThis);
	}

	virtual const T & Get(int index) const   // return item at index
	{
		ValidateIndex(index);

		Node* n = head;
		for (int i = index; i < index; i++) {
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

		virtual bool HasNext() const    // returns true if there is a next item
		{
			return currentNode != nullptr;		
		}

		virtual T & Next()              // returns next item and advances iterator toward end
		{
			if (HasNext()) {
				T& returnThis = currentNode->item;
				currentNode = currentNode->next;
				return returnThis;
			}
			throw "No next node for iterator!(LinkedListIter)";		
		}

		virtual bool HasPrevious() const// returns true if there is a previous item
		{
			// TODO
			throw "TODO";
		}

		virtual T & Previous()          // returns previous item and advances iterator toward beginning
		{
			// TODO
			throw "TODO";
		}

		virtual void Insert(const T & item)  // inserts item at current position, making room as needed
		{
			// TODO
			throw "TODO";
		}

		virtual T Remove()        // removes item at current position, contracting the list
		{
			if (currentNode == nullptr) {
				throw "Cannot remove past end of list";
			}

			Node* nukeThis = currentNode;
			currentNode = currentNode->next;
			return theList->RemoveNode(nukeThis);
		}

		const T & Get() const
		{
			// TODO
			throw "TODO";
		}
	};

	virtual List<T>::ListIterator * Begin()  // returns new iterator at beginning of list
	{
		return new LinkedListIterator(this, head);
	}

	virtual List<T>::ListIterator * End()    // returns new iterator past end of list
	{
		// TODO
		throw "TODO";
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

		if (prevOne == nullptr)
		{
			head = nextOne;
		}
		else {
			prevOne->next = nextOne;
		}

		if (nextOne == nullptr)
		{
			tail = prevOne;
		}
		else {
			nextOne->prev = prevOne;
		}

		T returnThis = nukeThis->item;
		delete nukeThis;
		count--;

		return returnThis;

	}
};


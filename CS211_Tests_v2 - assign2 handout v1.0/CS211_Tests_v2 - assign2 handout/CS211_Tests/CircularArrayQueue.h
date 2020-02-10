// CircularArrayQueue.h
// Pete Myers, OIT Winter 2020
// Implementation of the abstract queue interface using a circular array
//
// Handout Assignment 2
// By Kate LaFrance
//

#pragma once

#include "Queue.h"

template <class T> class CircularArrayQueue: public Queue<T>
{
private:
	T* contents;
	int head, tail, count, capacity;

public:
	CircularArrayQueue():head(0), tail(0), count(0), capacity(10)
	{
		// Initialize empty Queue
		contents = new T[capacity];
	}

	virtual int Count() const		     // Return the number of items in the queue
	{
		return count;
	}

	virtual void Insert(const T & item) // insert item into the queue at tail
	{
		Grow();
		contents[tail] = item;
		tail = (tail + 1) % capacity;
		count++;
	}

	virtual T Remove()                  // remove next item from head of queue
	{
		if (count <= 0) {
			throw "(Remove)CircularArray Queue is Empty!!";
		}
		
		T item = contents[head];
		head = (head + 1)% capacity;
		count--;
		
		return item;
	}

	virtual const T & Peek() const      // return item at head of queue, leave it there
	{

		/*if (!Empty()) {
			return contents[head];
		}
		else {
			throw "Peek is empty broken";
		}*/


		if (count <= 0) {
			throw "(Peek)CircularArray Queue is Empty!!";
		}

		return contents[head];
	}

private:
	
	void Grow() {
		// Doubles capacity of array, if necessary.
		if (count >= capacity) {

			// Create a new array with 2x capacity.
			T* newArray = new T[capacity* 2];

			// Copy old contents to new array.
			// Copy (head ti end of old array) into new array.
			int newIndex = 0;
			for (int oldIndex = head; oldIndex < capacity; oldIndex++, newIndex++) {
				newArray[newIndex] = contents[oldIndex];
			}

			// Copy (beginning of old array to tail) into new array
			for (int oldIndex = 0; oldIndex < tail; oldIndex++, newIndex++) {
				newArray[newIndex] = contents[oldIndex];
			}

			// Reset head and tail
			head = 0;
			tail = count;

			// Delete old and keep new.
			delete [] contents;
			contents = newArray;

			capacity *= 2;


		}

	}

	bool isEmpty() {
		bool empty;
		if (count <= 0) {
			throw "(Peek)CircularArray Queue is Empty!!";
			empty = true;
		}
		else {
			empty = false;
		}

		return empty;
	}
	
};

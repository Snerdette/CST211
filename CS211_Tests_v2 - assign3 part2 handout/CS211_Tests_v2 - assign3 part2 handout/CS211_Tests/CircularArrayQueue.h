// CircularArrayQueue.h
// Pete Myers, OIT Winter 2020
// Implementation of the abstract queue interface using a circular array
//
// Handout Assign2
//

#pragma once

#include "Queue.h"

template <class T> class CircularArrayQueue: public Queue<T>
{
private:
	// TODO

public:
	CircularArrayQueue()
	{
		// TODO
	}

	virtual int Count() const		     // return the number of items in the queue
	{
		// TODO
		throw "TODO";
	}

	virtual void Insert(const T & item) // insert item into the queue at tail
	{
		// TODO
		throw "TODO";
	}

	virtual T Remove()                  // remove next item from head of queue
	{
		// TODO
		throw "TODO";
	}

	virtual const T & Peek() const      // return item at head of queue, leave it there
	{
		// TODO
		throw "TODO";
	}

private:
	// TODO
	
};

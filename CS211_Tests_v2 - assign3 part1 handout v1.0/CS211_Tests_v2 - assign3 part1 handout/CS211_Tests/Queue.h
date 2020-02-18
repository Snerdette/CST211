// Queue.h
// Pete Myers, OIT Winter 2020
// Abstract interface for the Queue data structure

#pragma once

template <class T> class Queue
{
public:
	virtual int Count() const = 0;		     // return the number of items in the queue
	virtual void Insert(const T & item) = 0; // insert item into the queue at tail
	virtual T Remove() = 0;                  // remove next item from head of queue
	virtual const T & Peek() const = 0;      // return item at head of queue, leave it there
};

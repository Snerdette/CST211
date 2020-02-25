// Stack.h
// Pete Myers, OIT Winter 2020
// Abstract interface for the Stack data structure

#pragma once

template <class T> class Stack
{
public:
	virtual int Count() const = 0;				// return the number of items in the stack
	virtual void Push(const T & item) = 0;		// push item onto the stack
	virtual T Pop() = 0;						// pop top item from the stack
	virtual const T & Peek() const = 0;			// return item at top of stack, leave it there
};


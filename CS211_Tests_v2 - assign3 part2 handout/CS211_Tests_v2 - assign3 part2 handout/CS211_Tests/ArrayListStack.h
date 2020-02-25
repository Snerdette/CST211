// ArrayListStack.h
// Pete Myers, OIT Winter 2020
// Implementation of Stack data structure using an ArrayList
//
// Handout Assign2
//

#pragma once

#include "Stack.h"
#include "ArrayList.h"

template <class T> class ArrayListStack : public Stack<T>
{
private:
	// TODO

public:
	ArrayListStack()
	{
		// TODO
	}
	
	virtual int Count() const		// returns the number of items in the stack
	{
		// TODO
		throw "TODO";
	}

	virtual void Push(const T & item)    // push item onto the stack
	{
		// TODO
		throw "TODO";
	}

	virtual T Pop()            // pop top item from the stack
	{
		// TODO
		throw "TODO";
	}

	virtual const T & Peek() const   // return item at top of stack, leave it there
	{
		// TODO
		throw "TODO";
	}
};


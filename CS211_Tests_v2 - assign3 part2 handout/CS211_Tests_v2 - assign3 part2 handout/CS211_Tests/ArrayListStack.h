// ArrayListStack.h
// Pete Myers, OIT Winter 2020
// Implementation of Stack data structure using an ArrayList
//
// Handout Assignment 2
// By Kate LaFrance
//

#pragma once

#include "Stack.h"
#include "ArrayList.h"

template <class T> class ArrayListStack : public Stack<T>
{
private:
	ArrayList<T> contents;

public:
	ArrayListStack()
	{
		// Nothing needed here...so far...
	}

	virtual int Count() const		// returns the number of items in the stack
	{
		return contents.Count();
	}

	virtual void Push(const T& item)    // push item onto the stack
	{
		contents.Append(item);
	}

	virtual T Pop()            // pop top item from the stack
	{
		// "POP"s the olast item from the ArrayList
		return contents.Remove(contents.Count() - 1);
	}

	virtual const T& Peek() const   // return item at top of stack, leave it there
	{
		return contents.Get(contents.Count() - 1);
	}
};


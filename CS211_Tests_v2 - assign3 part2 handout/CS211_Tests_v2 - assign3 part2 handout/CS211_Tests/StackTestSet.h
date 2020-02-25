// StackTestSet.h
// Unit tests for Stack data structures in CST211 C++
// Winter 2020
// Pete Myers

#pragma once

#include "TestBase.h"

#include "ArrayListStack.h"

typedef Stack<std::string>* (*StackCreator)();

Stack<std::string>* ArrayListStackCreator()
{
	return new ArrayListStack<std::string>();
}

class StackTestSet : public TestSet
{
public:
	StackTestSet(StackCreator creator, const std::string& student, const std::string& setName, const std::string& description) :
		TestSet(setName, description)
	{
		AddTest("Push / Peek", "Push(), Peek()", 1, PushPeekTest, creator);
		AddTest("Push / Pop", "Push(), Pop()", 1, PushPopTest, creator);
		AddTest("Count", "Push(), Pop(), Count()", 1, CountTest, creator);
		AddTest("Pop / Peek error", "Push(), Pop(), Peek()", 1, PopPeekErrorTest, creator);
	}

private:
	static void PushPeekTest(void* param)
	{
		StackCreator stackCreator = (StackCreator)param;
		Stack<std::string>* stack = stackCreator();

		stack->Push("a");
		Verify(stack->Peek() == "a", "Push('a'), Peek() == 'a'");
		stack->Push("b");
		Verify(stack->Peek() == "b", "Push('b'), Peek() == 'b'");
		stack->Push("c");
		Verify(stack->Peek() == "c", "Push('c'), Peek() == 'c'");

		delete stack;
	}

	static void PushPopTest(void* param)
	{
		StackCreator stackCreator = (StackCreator)param;
		Stack<std::string>* stack = stackCreator();

		stack->Push("a");
		Verify(stack->Pop() == "a", "Push('a'), Pop() == 'a'");
		stack->Push("b");
		stack->Push("c");
		Verify(stack->Pop() == "c", "Push('b'), Push('c'), Pop() == 'c'");
		Verify(stack->Pop() == "b", "Pop() == 'b'");

		delete stack;
	}

	static void CountTest(void* param)
	{
		StackCreator stackCreator = (StackCreator)param;
		Stack<std::string>* stack = stackCreator();

		Verify(stack->Count() == 0, "Count() == 0");
		stack->Push("a");
		Verify(stack->Count() == 1, "Push('a'), Count() == 1");
		std::string s = stack->Pop();
		Verify(s == "a" && stack->Count() == 0, "Pop() == 'a', Count() == 0");

		delete stack;
	}

	static void PopPeekErrorTest(void* param)
	{
		StackCreator stackCreator = (StackCreator)param;
		Stack<std::string>* stack = stackCreator();

		VerifyException([](void* p) -> void { std::string val = ((Stack<std::string>*)p)->Peek(); }, stack, "", "Peek()");
		VerifyException([](void* p) -> void { std::string val = ((Stack<std::string>*)p)->Pop(); }, stack, "", "Pop()");
		stack->Push("a");
		std::string s = stack->Pop();
		VerifyException([](void* p) -> void { std::string val = ((Stack<std::string>*)p)->Peek(); }, stack, "", "Push('a'), Pop(), Peek()");
		VerifyException([](void* p) -> void { std::string val = ((Stack<std::string>*)p)->Pop(); }, stack, "", "Pop()");
		stack->Push("b");
		s = stack->Pop();
		VerifyException([](void* p) -> void { std::string val = ((Stack<std::string>*)p)->Peek(); }, stack, "", "Push('b'), Pop(), Peek()");
		VerifyException([](void* p) -> void { std::string val = ((Stack<std::string>*)p)->Pop(); }, stack, "", "Pop()");

		delete stack;
	}
};

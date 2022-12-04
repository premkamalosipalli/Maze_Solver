//pragma once is a non standard pre-processor derivative.
#pragma once
#include "IterativePosition.h"

class Stack
{
private:
	Position* base;
	int stackTop;
	int sizeOfStack;
	int lengthOfStack;

public:
	Stack(int size)
	{
		base = new Position[size];
		sizeOfStack = size;
		stackTop = -1;
		lengthOfStack = 0;
	}

	~Stack()
	{
		delete[]base;
		stackTop = -1;
		sizeOfStack = 0;
		lengthOfStack = 0;
	}

	int Push(Position elem)
	{
		// when stack is full return 1.
		if (stackTop == sizeOfStack - 1) return 1; 
		// when stack is not full then return 0. 
		else
		{
			stackTop++;
			base[stackTop] = elem;
			lengthOfStack++;
			return 0;   
		}
	}

	Position Pop()
	{
		Position error;
		error.first = -1;
		error.second = -1;

		Position correct;

		// If stack is empty then return error.
		if (stackTop == -1) return error;   
		else
		{
			// If stack is not empty then return a existing position.
			correct = base[stackTop];
			stackTop--;
			lengthOfStack--;
			return correct;   
		}
	}

	// Return the length of the stack.
	int GetLength()
	{
		return lengthOfStack;
	}
};


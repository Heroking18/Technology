#ifndef __QUEUEH__
#define __QUEUEH__
#include "stack.h"
#include <cstddef>
#include <cstdint>

class Queue
{
private:
	Stacks *stack_in;
	Stacks *stack_out;
	size_t item_size;

public:
	// Constructor
	Queue(size_t);

	int myqueue_enqueue(void *obj);
	int myqueue_dequeue(void *obj);

	Stacks *getStack_in()
	{
		return stack_in;
	}

	Stacks *getStack_out()
	{
		return stack_out;
	}

	size_t getItem_size()
	{
		return item_size;
	}

	// Destructor
	~Queue();
};

#endif
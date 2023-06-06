#ifndef __STACKH__
#define __STACKH__
#include <cstddef>
#include <cstdint>

struct Node
{
	void *obj;
	Node *next;
};

class Stacks
{
private:
	Node *stack;
	size_t objsize;
	int numelem;

public:
	// Constructor
	Stacks(size_t);

	int mystack_push(void *obj);
	int mystack_pop(void *obj);
	int mystack_nofelem();

	Node *getStack()
	{
		return stack;
	}

	size_t getObjsize()
	{
		return objsize;
	}

	int getNumelem()
	{
		return numelem;
	}

	// Destructor
	~Stacks();
};

#endif

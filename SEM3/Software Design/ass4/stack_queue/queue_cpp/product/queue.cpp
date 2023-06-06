#include "queue.h"
#include "stack.h"
#include <iostream>
#include <string.h>

using namespace std;

//  constructor definition
Queue::Queue(size_t size)
{
    if (size > 0)
    {
        stack_in = new Stacks(size);
        stack_out = new Stacks(size);
        item_size = size;
    }
}

//  destructor definition
Queue::~Queue()
{
    delete (stack_in);
    delete (stack_out);
}

int Queue::myqueue_enqueue(void *obj)
{
    if (stack_in->mystack_push(obj) != 0)
    {
        return -1;
    }

    return 0;
}

int Queue::myqueue_dequeue(void *obj)
{
    if (stack_out->getStack() == NULL)
    {
        while (stack_in->getNumelem() != 0)
        {
            stack_in->mystack_pop(obj);
            stack_out->mystack_push(obj);
        }
    }
    if (stack_out->getNumelem() == 0)
    {
        return -1;
    }
    stack_out->mystack_pop(obj);
    return 0;
}
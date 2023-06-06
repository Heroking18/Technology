#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include <stdint.h>
#include <unistd.h>

#include "mystack.h"
#include "myqueue.h"

QueueMeta_t *myqueue_create(int item_size)
{
	QueueMeta_t *elem = NULL;
	if (item_size <= 0)
	{
		return NULL;
	}
	elem = (QueueMeta_t *)malloc(sizeof(QueueMeta_t));
	if (elem == NULL)
	{
		return NULL;
	}
	elem->stack_in = mystack_create(item_size); // stack_in & stack_out is created using mystack_create()
	elem->stack_out = mystack_create(item_size);
	elem->item_size = item_size; // size of the datatype is set

	return elem;
}

void myqueue_delete(QueueMeta_t *queue)
{
	mystack_destroy(queue->stack_in); // myqueue_delete uses destroy function from mystack to clean the stacks inside
	mystack_destroy(queue->stack_out);
	free(queue);
}

int myqueue_enqueue(QueueMeta_t *que, void *obj)
{
	if (que == NULL || que->stack_in == NULL || obj == NULL)
	{
		return -1;
	}

	mystack_push(que->stack_in, obj); // enqueue the obj inside stack_in stack.

	return 0;
}

int myqueue_dequeue(QueueMeta_t *queue, void *obj)
{
	if (queue == NULL || obj == NULL)
	{
		return -1;
	}

	if (queue->stack_out->stack == NULL)
	{
		while (queue->stack_in->numelem != 0) // pops all the elem inside stack_in and pushes it inside stack_out to follow the FIFO order.
		{
			mystack_pop(queue->stack_in, obj);
			mystack_push(queue->stack_out, obj);
		}
	}
	if(queue->stack_out->numelem == 0)
	{
		return -1;
	}
	mystack_pop(queue->stack_out, obj); // pops out the first obj of stack_out stack

	return 0;
}

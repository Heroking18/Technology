
#include "mystack.h"
#include "logging.h"
#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>
/* The stack is an abstract data type.
 * this means that the internal structures are
 * never exposed to the users of the library.
 */

/* Note: the stacks have no knowledge of what types
 * they are storing. This is not a concern of the stack
 */

StackMeta_t *mystack_create(size_t objsize)
{
  StackMeta_t *stack;
  if (objsize <= 0)
  {
    return NULL;
  }
  stack = (StackMeta_t *)malloc(sizeof(StackMeta_t));
  if (stack == NULL)
  {
    return NULL;
  }
  else
  {
    stack->stack = NULL;      // my actual stack basically the first stack(the top)
    stack->objsize = objsize; // size of the datatype
    stack->numelem = 0;       // total count of elem inside the stack
  }
  return stack;
}

int mystack_push(StackMeta_t *stack, void *obj)
{
  if (stack == NULL) // check if stack is not created
  {
    return -1;
  }

  StackObject_t *nodeObject = NULL;
  nodeObject = (StackObject_t *)malloc(sizeof(StackObject_t));
  if (nodeObject == NULL) // check if nodeObject is not created
  {
    return -1;
  }

  nodeObject->obj = malloc(stack->objsize); // allocate memory for void *obj
  if (stack->stack == NULL)
  {
    nodeObject->next = NULL;
  }
  else
  {
    nodeObject->next = stack->stack;
  }
  memcpy(nodeObject->obj, obj, stack->objsize); // copies the obj to nodeObject obj
  stack->stack = nodeObject;
  stack->numelem++;

  return 0;
}

int mystack_pop(StackMeta_t *stack, void *obj)
{
  if (stack->stack == NULL)
  {
    return -1;
  }
  StackObject_t *temp = NULL;
  memcpy(obj, stack->stack->obj, stack->objsize); // stores obj outside the function for later use before freeing
  temp = stack->stack;
  stack->numelem--;
  stack->stack = stack->stack->next;
  free(temp->obj);
  free(temp);
  return 0;
}

void mystack_destroy(StackMeta_t *stack)
{
  StackObject_t *prevNode;
  StackObject_t *tempNode = stack->stack;
  while (tempNode != NULL) // frees the node infront of prevNode which is tempNode. This will free until stack is empty.
  {
    prevNode = tempNode;
    tempNode = tempNode->next;
    free(prevNode->obj);
    free(prevNode);
    stack->numelem--;
  }
  free(stack);
}

int mystack_nofelem(StackMeta_t *stack)
{
  if (stack == NULL)
  {
    return -1;
  }

  if (stack->stack == NULL)
  {
    return 0;
  }
  else
  {
    return stack->numelem;
  }
}

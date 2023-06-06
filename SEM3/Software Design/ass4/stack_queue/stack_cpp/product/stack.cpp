#include "stack.h"
#include <iostream>
#include <string.h>

using namespace std;

//  constructor definition
Stacks::Stacks(size_t size)
{
    if (size > 0)
    {
        stack = nullptr;
        objsize = size;
        numelem = 0;
    }
}

//  destructor definition
Stacks::~Stacks()
{
    Node *tempNode = NULL;
    while (stack != NULL)
    {
        tempNode = stack;
        stack = tempNode->next;
        ::operator delete(tempNode->obj);
        delete (tempNode);
        numelem--;
    }
}

int Stacks::mystack_push(void *obj)
{
    Node *stackNode = new Node;
    if (stackNode == nullptr) // check if nodeObject is not created
    {
        return -1;
    }

    stackNode->obj = ::operator new(objsize); // allocate memory for void *obj
    if (stack == nullptr)
    {
        stackNode->next = nullptr;
    }
    else
    {
        stackNode->next = stack;
    }
    memcpy(stackNode->obj, obj, this->objsize); // copies the obj to nodeObject obj
    stack = stackNode;
    numelem++;
    return 0;
}

int Stacks::mystack_pop(void *obj)
{
    if (stack == nullptr)
    {
        return -1;
    }
    Node *temp = nullptr;
    temp = stack;
    memcpy(obj, temp->obj, this->objsize);
    stack = temp->next;
    numelem--;
    ::operator delete(temp->obj);
    delete temp;
    return 0;
}

int Stacks::mystack_nofelem()
{
    if (numelem < 0)
    {
        return -1;
    }
    return numelem;
}
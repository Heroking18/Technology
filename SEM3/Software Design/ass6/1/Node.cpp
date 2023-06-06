#include "Node.h"
#include <iostream>

Node::Node()
{
}

Node::Node(int Value)
{
    value = Value;
    Left = NULL;
    Right = NULL;
}

Node::~Node()
{
    delete Left;
    delete Right;
}
#pragma once

class Node
{
public:
    int value = 0;
    int level = 0;
    Node *Left;
    Node *Right;

    Node();
    Node(int);
    ~Node();
};
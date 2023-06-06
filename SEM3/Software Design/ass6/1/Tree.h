#pragma once
#include <iostream>
#include "Node.h"

class Tree
{
private:
    int max_depth = 0;

public:
    Node *root;

    Tree();
    Tree(int key);
    ~Tree();

    int getMax_depth();
    void addNode(int sourceNodeKey, int key, bool isLeft);
    Node *findNode(Node *node, int key);
    Node *findNode(int key);
};
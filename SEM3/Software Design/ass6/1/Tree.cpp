#include "Tree.h"

using namespace std;

Tree::Tree()
{
    root = NULL;
}
Tree::Tree(int key)
{
    root = new Node(key);
    max_depth = 1;
    root->level = 1;
}

Tree::~Tree()
{
    if (root != NULL)
    {
        delete root;
    }
}

int Tree::getMax_depth()
{
    return max_depth;
}

void Tree::addNode(int sourceNodeKey, int key, bool isLeft)
{
    if (key == 0)
    {
        return;
    }

    Node *node = findNode(sourceNodeKey);
    if (node == NULL)
    {
        return;
    }

    // create new node with the given key
    Node *elem = new Node(key);
    if (elem == NULL)
    {
        return;
    }

    // calculate new depth of the tree and set level of new node to the new depth
    int new_depth = node->level + 1;
    elem->level = new_depth;

    // if the new node is to be added as left child, set the Left property of the parent node to the new node
    if (isLeft)
    {
        node->Left = elem;
    }
    else
    {
        node->Right = elem;
    }

    if (max_depth < new_depth)
    {
        max_depth = new_depth;
    }
}

Node *Tree::findNode(Node *node, int key)
{
    if (node == NULL)
    {
        return NULL;
    }

    if (key == node->value)
    {
        return node;
    }

    // recursively search right and left the subtree
    Node *res = findNode(node->Right, key);
    if (res == NULL)
    {
        res = findNode(node->Left, key);
    }
    return res;
}

Node *Tree::findNode(int key)
{
    if (root != NULL)
    {
        return findNode(root, key);
    }
    else
    {
        return NULL;
    }
}
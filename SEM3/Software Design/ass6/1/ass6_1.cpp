#include <iostream>
#include "Tree.h"

using namespace std;

int main()
{
	int n;
	cin >> n;

	Tree *tree = NULL;

	for (int i = 0; i < n; i++)
	{
		int nr, left, right;
		cin >> nr >> left >> right;

		// if this is the first node, create a new tree with the given node number
		if (i == 0)
		{
			tree = new Tree(nr);

			// add left and right children to the tree
			tree->addNode(nr, left, true);
			tree->addNode(nr, right, false);
		}
		else
		{
			tree->addNode(nr, left, true);
			tree->addNode(nr, right, false);
		}
	}

	// if the tree is still empty
	if (tree == NULL)
	{
		return 0;
	}
	int depth = tree->getMax_depth(); // get depth of tree
	/* implement your algorithm and store the tree depth in depth */
	cout << "depth is " << depth << endl;
	return 0;
}

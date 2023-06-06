/* SD exercise 1: simple linked list API */
/* Author : R. Frenken                   */
/* Version : 1.0			 */
#include "linkedlist.h"
#include <stdlib.h>

/***************************************************/
/* If *list == NULL, a new list should be created, */
/* otherwise prepend a new ITEM with value value   */
/* to the existing list                            */
/* Returns -1 if not enough memory, otherwise 0    */
/***************************************************/

int add_first(ITEM **list, int value)
{
	/* Implement */
	ITEM *elem;
	if (*list == NULL)
	{
		elem = malloc(sizeof(ITEM));
		if (elem == NULL)
		{
			return -1;
		}
		elem->next = NULL;
		elem->value = value;
		*list = elem;
	}
	else
	{
		elem = malloc(sizeof(ITEM));
		if (elem == NULL)
		{
			return -1;
		}
		elem->next = *list;
		elem->value = value;
		*list = elem;
	}
	return 0;
}

/***************************************************/
/* If *list == NULL, a new list should be created, */
/* otherwise append a new ITEM with value value to */
/* the existing list                               */
/* Returns -1 if not enough memory, otherwise 0    */
/***************************************************/

int add_last(ITEM **list, int value)
{
	/* Implement to fix */
	// create new node elem
	ITEM *elem = malloc(sizeof(ITEM));
	if (elem == NULL)
	{
		return -1;
	}
	elem->next = NULL;
	elem->value = value;

	// if head (first element is NULL, it is an empty list)
	if (*list == NULL)
	{
		*list = elem;
	}
	// else find last node
	else
	{
		ITEM *lastNode = *list;
		ITEM *a = *list;
		while (a->next != NULL) // last nodes address should be NULL
		{
			lastNode = a->next;
			a = a->next;
		}
		lastNode->next = elem;
	}
	return 0;
}

/****************************************************/
/* Insert a new item after current item c_item      */
/* Returns -1 if not enough memory, c_item == NULL, */
/* *list == NULL or c_item not found, otherwise 0   */
/****************************************************/

int add_after(ITEM *list, ITEM *c_item, int value)
{
	/* Implement */
	ITEM *elem;
	if (list == NULL || c_item == NULL)
	{
		return -1;
	}
	else
	{
		elem = malloc(sizeof(ITEM));
		if (elem == NULL)
		{
			return -1;
		}

		ITEM *temp = list;
		while (temp->next != NULL) // traverse the list if c_item is found
		{
			if (temp == c_item)
			{
				break;
			}
			temp = temp->next;
		}
		elem->value = value;
		ITEM *old_after = c_item->next;
		c_item->next = elem;
		elem->next = old_after;
	}
	return 0;
}

/***************************************************/
/* Remove first item of the list                   */
/* Returns -1 if list==NULL, otherwise 0           */
/***************************************************/

int rem_first(ITEM **list)
{
	/* Implement */
	ITEM *elem;
	if (*list == NULL)
	{
		return -1;
	} // if list is empty
	else
	{
		elem = *list;
		*list = (*list)->next;
		free(elem);
	}

	return 0;
}

/***************************************************/
/* Remove last item of the list                    */
/* Returns -1 if list==NULL, otherwise 0           */
/***************************************************/

int rem_last(ITEM **list)
{
	/* Implement */
	ITEM *lastNode = *list;
	if (*list == NULL)
	{
		return -1;
	} // if list is empty
	if (lastNode->next == NULL)
	{
		*list = NULL;
	}
	else
	{
		ITEM *secondLastNode;
		while (lastNode->next != NULL)
		{
			secondLastNode = lastNode;
			lastNode = lastNode->next;
		}
		free(lastNode);
		secondLastNode->next = NULL;
	}
	return 0;
}

/***************************************************/
/* Remove item after c_item of the list            */
/* Returns -1 list==NULL, c_item not found or      */
/* c_item is the last_element                      */
/***************************************************/

int rem_after(ITEM *list, ITEM *c_item)
{
	/* Implement */
	if (list == NULL || c_item->next == NULL)
	{
		return -1;
	}

	ITEM *temp = list;
	while (temp->next != NULL) // traverse the list if c_item is found
	{
		if (temp == c_item)
		{
			break;
		}
		temp = temp->next;
	}
	ITEM *old_after = c_item->next;
	c_item->next = old_after->next;
	free(old_after);
	return 0;
}

/*********************************************************/
/* All dynamic memory allocated to the list is freed     */
/* Empty list should point to NULL                       */
/*********************************************************/

void clean(ITEM **list)
{
	/* Implement */
	ITEM *prevNode;
	ITEM *tempNode = *list;
	while (tempNode != NULL)
	{
		prevNode = tempNode;	   // copy tempNode to elem
		tempNode = tempNode->next; // go to next node
		free(prevNode);			   // free previous node
	}
	*list = NULL;
	return;
}

#include "MemoryManager.h"
#include "MList.h"
#include <iostream>

using namespace std;

/* Starting point for MemoryManager constructor */
MemoryManager::MemoryManager()
{
	allocList = new AllocList(memStart, maxSize);
	freeList = new FreeList(memStart, maxSize);
}

/* Code correct destructor to cleanup all memory */
MemoryManager::~MemoryManager()
{
	delete allocList;
	delete freeList;
}

/* pre : size > 0
 * post: If no memory block of size "size" available return -1
 *       Otherwise claimMemory() returns the first
 *       address in the freeList where a memory block of at least size is present.
 *       This memory is allocated and not any more available.
 *       The newly allocated block is added to the allocList and addr of the newly
 *       allocated block is returned
 */

int MemoryManager::claimMemory(int size)
{
	// Start at the head of the freeList
	ITEM *free_elem = freeList->head;
	ITEM *alloc_elem = allocList->head;

	if (free_elem == NULL) // check if there is no free memory
	{
		return -1;
	}

	// Iterate through freeList to find a block of memory that is large enough
	while (free_elem->_size < size)
	{
		if (free_elem->next == NULL)
		{
			return -1;
		}
		free_elem = free_elem->next;
	}

	// Save the address of the block of memory found
	int addr = free_elem->_addr;
	ITEM *new_elem = new ITEM(addr, size);

	// add allocated block to allocList
	if (alloc_elem == NULL)
	{
		allocList->add_first(new_elem);
	}
	else
	{
		// Insert block in the correct position in the list
		if (alloc_elem->_addr > new_elem->_addr)
		{
			allocList->add_first(new_elem);
		}
		else
		{
			while (alloc_elem->next != NULL && alloc_elem->next->_addr < free_elem->_addr)
			{
				alloc_elem = alloc_elem->next;
			}
			allocList->add_after(new_elem, alloc_elem);
		}
	}

	// update freeList
	free_elem->_addr += size;
	free_elem->_size -= size;
	if (free_elem->_size == 0)
	{
		freeList->rem_after(free_elem);
	}
	delete new_elem;

	return addr;
}

/* pre:  Parameter addr must match the start of an allocatd memory block. Otherwhise return -1.
 *
 * post: If addr is a part of allocated memory of allocList then the memory from this address
 * 	     with registered size should be removed from the allocList and added to the freeList
 *
 *       freeMemory(addr) returns number of bytes (size) belongig to the address addr
 *       In all other cases freeMemory(freeList,allocList,addr) returns -1.
 */

int MemoryManager::freeMemory(int addr)
{
	// check if allocList is empty
	if (allocList->head == NULL)
	{
		return -1;
	}

	ITEM *elem;
	ITEM *current_alloc_elem = allocList->head;
	ITEM *prev_alloc_elem = NULL;

	// Iterate through allocList to find block to be freed
	while (current_alloc_elem != NULL)
	{
		if (current_alloc_elem->_addr == addr)
		{
			elem = new ITEM(addr, current_alloc_elem->_size);

			// remove block from allocList
			if (prev_alloc_elem == NULL)
			{
				allocList->rem_first();
			}
			else
			{
				prev_alloc_elem->next = current_alloc_elem->next;
			}
			break;
		}
		prev_alloc_elem = current_alloc_elem;
		current_alloc_elem = current_alloc_elem->next;
	}

	// if block not found
	if (current_alloc_elem == NULL)
	{
		return -1;
	}

	ITEM *free_elem = freeList->head;
	ITEM *prev_free_elem = NULL;

	// iterate through freeList to find correct location to insert the freed block
	while (free_elem != NULL)
	{
		if (elem->_addr < free_elem->_addr)
		{
			if (prev_free_elem == NULL)
			{
				freeList->add_first(elem);
			}
			else
			{
				freeList->add_after(elem, prev_free_elem);
			}
			break;
		}
		prev_free_elem = free_elem;
		free_elem = free_elem->next;
	}

	// if reached at the end of the list, add the block after the last block
	if (free_elem == NULL)
	{
		freeList->add_after(elem, prev_free_elem);
	}
	int size = elem->_size;

	// iterate through freeList to check if current block can be merged to the next block
	ITEM *merge_current_elem = freeList->head;
	while (merge_current_elem->next != NULL)
	{

		if ((merge_current_elem->_addr + merge_current_elem->_size) == merge_current_elem->next->_addr)
		{
			ITEM *elemErased;
			elemErased = merge_current_elem->next;
			merge_current_elem->_size += merge_current_elem->next->_size;
			merge_current_elem->next = merge_current_elem->next->next;
			delete elemErased;
		}
		else
		{
			merge_current_elem = merge_current_elem->next;
		}
	}
	return size;
}

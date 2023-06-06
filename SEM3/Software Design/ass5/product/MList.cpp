#include <iostream>
#include "MList.h"

using namespace std;

/* Implementation of all your MList methods */

MList::MList()
{
}
MList::~MList()
{
    cleanList();
    delete head;
}

int MList::add_first(ITEM *list)
{

    if (head == NULL)
    {
        head = list;
    }
    else
    {
        list->next = head;
        head = list;
    }

    return 0;
}

int MList::add_after(ITEM *list, ITEM *c_item)
{
    list->next = c_item->next;
    c_item->next = list;
    return 0;
}
int MList::rem_first()
{
    if (head == NULL)
    {
        return -1;
    }
    else
    {
        if (head->next == NULL)
        {
            head = NULL;
        }
        else
        {
            ITEM *elem;

            elem = head;
            head = head->next;
            delete elem;
        }
        return 0;
    }
}
int MList::rem_after(ITEM *list)
{
    ITEM *elem = head;
    ITEM *prev = nullptr;
    while (elem && elem != list)
    {
        prev = elem;
        elem = elem->next;
    }
    if (!elem)
    {
        return -1;
    }
    if (prev)
    {
        prev->next = elem->next;
    }
    else
    {
        head = elem->next;
    }
    delete elem;
    return 0;
}

void MList::cleanList()
{
    while (head != NULL)
    {
        ITEM *temp = head;
        head = head->next;
        delete temp;
    }
}
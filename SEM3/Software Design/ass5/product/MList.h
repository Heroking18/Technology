#pragma once
typedef struct ITEM
{
    int _addr;
    int _size;
    struct ITEM *next = 0;
    ITEM(int addr, int size)
    {
        _addr = addr;
        _size = size;
    }
} ITEM;

class MList
{
public:
    ITEM *head = 0;
    ITEM *tail = 0;
    MList();  // constructor
    ~MList(); // destructor
    /* all MList methods should come here */
    int add_first(ITEM *list);
    int add_after(ITEM *list, ITEM *c_item);
    int rem_first();
    int rem_after(ITEM *list);
    void cleanList();
};

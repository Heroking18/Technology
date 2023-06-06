#include "queue.h"

Queue::Queue()
{
}

Queue::~Queue()
{
}

void Queue::push(int x)
{
    queue.push_back(x);
}

void Queue::pop()
{
    if (!queue.empty())
    {
        queue.erase(queue.begin());
    }
}

int Queue::front()
{
    if (!queue.empty())
    {
        return queue[0];
    }
    return -1;
}

bool Queue::empty()
{
    return queue.empty();
}
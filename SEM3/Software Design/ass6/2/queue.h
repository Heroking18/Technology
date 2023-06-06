#pragma once
#include <iostream>
#include <vector>

using namespace std;

const int MAX = 100000;

class Queue
{
private:
    std::vector<int> queue;

public:
    Queue();
    ~Queue();

    void push(int x);
    void pop();
    int front();
    bool empty();
};

#ifndef NODE_H
#define NODE_H

#include <iostream>

using namespace std;

template <typename ITEM_TYPE>
struct node
{
public:
    ITEM_TYPE _item;
    node *_next;
    node(const ITEM_TYPE &item = ITEM_TYPE(), node *next = nullptr);
    template <typename T>
    friend std::ostream &operator<<(std::ostream &outs, const node<T> &printMe);
};

#include "node.cpp"

#endif
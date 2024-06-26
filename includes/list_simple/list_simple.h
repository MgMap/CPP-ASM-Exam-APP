#ifndef LIST_SIMPLE_H
#define LIST_SIMPLE_H
#include <assert.h>
#include "../node/node.h"
#include "../linked_list_functions/linked_list_functions.h"

#include <iostream>

using namespace std;

template <class ITEM_TYPE>
class List
{
public:
    List();

    ~List();
    List(const List<ITEM_TYPE> &copyThis);
    List &operator=(const List &RHS);

    node<ITEM_TYPE> *insert_head(ITEM_TYPE i); // inset i at the head of list

    node<ITEM_TYPE> *insert_after(ITEM_TYPE i, // insert i after iMarker
                                  node<ITEM_TYPE> *iMarker);

    node<ITEM_TYPE> *insert_before(ITEM_TYPE i, // insert i before iMarker
                                   node<ITEM_TYPE> *iMarker);

    node<ITEM_TYPE> *insert_sorted(ITEM_TYPE i); // insert i. Assume sorted list

    ITEM_TYPE Delete(node<ITEM_TYPE> *iMarker); // delete node pointed to by iMarker

    void Print() const; // print the list

    node<ITEM_TYPE> *search(const ITEM_TYPE &key); // return pointer to node containing
                                                   //   key. NULL if not there

    node<ITEM_TYPE> *prev(node<ITEM_TYPE> *iMarker); // get the previous node to iMarker

    ITEM_TYPE &operator[](int index); // return the item at index

    node<ITEM_TYPE> *begin() const; // return the head of the list

    node<ITEM_TYPE> *end() const;
    node<ITEM_TYPE> *last_node() const;

    bool empty() const { return head == nullptr; }

    int size() const { return _size; }
    template <class U>
    friend ostream &operator<<(ostream &outs, // insertion operator for list
                               const List<U> &l);

private:
    node<ITEM_TYPE> *head;
    int _size;
};

#include "list_simple.cpp"

#endif
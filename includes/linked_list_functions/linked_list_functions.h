#ifndef LINKED_LIST_FUNCTIONS_H
#define LINKED_LIST_FUNCTIONS_H

#include <iostream>

using namespace std;

// Linked List General Functions:
template <typename ITEM_TYPE>
void _print_list(node<ITEM_TYPE> *head);

// recursive fun! :)
template <typename ITEM_TYPE>
void _print_list_backwards(node<ITEM_TYPE> *head);

// return ptr to key or NULL
template <typename ITEM_TYPE>
node<ITEM_TYPE> *_search_list(node<ITEM_TYPE> *head, ITEM_TYPE key);

template <typename ITEM_TYPE>
node<ITEM_TYPE> *_insert_head(node<ITEM_TYPE> *&head, ITEM_TYPE insert_this);

// insert after ptr
// precondition: high level function checks if the node is in the array
template <typename ITEM_TYPE>
node<ITEM_TYPE> *_insert_after(node<ITEM_TYPE> *&head, node<ITEM_TYPE> *after_this, ITEM_TYPE insert_this);

// ptr to previous node
template <typename ITEM_TYPE>
node<ITEM_TYPE> *_previous_node(node<ITEM_TYPE> *head, node<ITEM_TYPE> *prev_to_this);

// insert before ptr
template <typename ITEM_TYPE>
node<ITEM_TYPE> *_insert_before(node<ITEM_TYPE> *&head, node<ITEM_TYPE> *before_this, ITEM_TYPE insert_this);

// delete, return item
template <typename ITEM_TYPE>
ITEM_TYPE _delete_node(node<ITEM_TYPE> *&head, node<ITEM_TYPE> *delete_this);
// duplicate the list...
template <typename ITEM_TYPE>
node<ITEM_TYPE> *_copy_list(node<ITEM_TYPE> *head);

// duplicate list and return the last node of the copy
template <typename T>
node<T> *_copy_list(node<T> *&dest, node<T> *src);

// delete all the nodes
template <typename ITEM_TYPE>
void _clear_list(node<ITEM_TYPE> *&head);

//_item at this position
template <typename ITEM_TYPE>
ITEM_TYPE &_at(node<ITEM_TYPE> *head, int pos);

//. . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . .
//      Sorted List Routines. order: 0: ascending, order: other: descending
//                              Assume a Sorted List
//. . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . .

template <typename ITEM_TYPE>
node<ITEM_TYPE> *_insert_sorted(node<ITEM_TYPE> *&head, ITEM_TYPE item, bool ascending = true);

// insert or add if a dup
template <typename ITEM_TYPE>
node<ITEM_TYPE> *_insert_sorted_and_add(node<ITEM_TYPE> *&head, ITEM_TYPE item, bool ascending = true);

// node after which this item goes order: 0 ascending
template <typename ITEM_TYPE>
node<ITEM_TYPE> *_where_this_goes(node<ITEM_TYPE> *head, ITEM_TYPE item, bool ascending = true);
// Last Node in the list
template <typename ITEM_TYPE>
node<ITEM_TYPE> *_last_node(node<ITEM_TYPE> *head);

#include "linked_list_functions.cpp"
#endif
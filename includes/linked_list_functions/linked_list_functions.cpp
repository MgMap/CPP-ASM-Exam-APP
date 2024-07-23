#ifndef LINKED_LIST_FUNCTIONS_CPP
#define LINKED_LIST_FUNCTIONS_CPP

#include "linked_list_functions.h"

// Linked List General Functions:
template <typename ITEM_TYPE>
void _print_list(node<ITEM_TYPE> *head)
{
    for (node<ITEM_TYPE> *walker = head; walker != nullptr; walker = walker->_next)
    {
        cout << *walker;
    }

    cout << "|||\n";
}

// recursive fun! :)
template <typename ITEM_TYPE>
void _print_list_backwards(node<ITEM_TYPE> *head)
{
    if (head != nullptr)
    {
        _print_list_backwards(head->_next);
        cout << *head;
    }

    else
        cout << "|||->";
}

// return ptr to key or NULL
template <typename ITEM_TYPE>
node<ITEM_TYPE> *_search_list(node<ITEM_TYPE> *head, ITEM_TYPE key)
{
    for (node<ITEM_TYPE> *walker = head; walker != nullptr; walker = walker->_next)
    {
        if (walker->_item == key)
            return walker;
    }

    return nullptr;
}

template <typename ITEM_TYPE>
node<ITEM_TYPE> *_insert_head(node<ITEM_TYPE> *&head, ITEM_TYPE insert_this)
{
    // 1. create a new node  // 2. _next point the same as headptr
    node<ITEM_TYPE> *temp = new node<ITEM_TYPE>(insert_this, head);

    // 3. head points to node
    head = temp;

    // return temp
    return temp;
}

// insert after ptr
// precondition: high level function checks if the node is in the array
template <typename ITEM_TYPE>
node<ITEM_TYPE> *_insert_after(node<ITEM_TYPE> *&head, node<ITEM_TYPE> *after_this, ITEM_TYPE insert_this)
{
    // empty list -> just add it
    if (head == nullptr)
    {
        _insert_head(head, insert_this);
        return head;
    }

    // create a new node with insert_this
    // and point the same as after_this is pointing
    node<ITEM_TYPE> *temp = new node<ITEM_TYPE>(insert_this, after_this->_next);
    after_this->_next = temp; // found's next points to new node

    return temp;
}

// ptr to previous node
template <typename ITEM_TYPE>
node<ITEM_TYPE> *_previous_node(node<ITEM_TYPE> *head, node<ITEM_TYPE> *prev_to_this)
{
    // assert if list is empty
    assert(prev_to_this);
    assert(head);

    // if prev_to_this is at the start
    if (head == prev_to_this)
    {
        return nullptr;
    }

    node<ITEM_TYPE> *walker = nullptr;
    // off by one be careful
    for (walker = head; walker->_next != prev_to_this; walker = walker->_next)
    {
        // something is wrong if not found
        assert(walker != nullptr);
    }
    return walker;
}

// insert before ptr
template <typename ITEM_TYPE>
node<ITEM_TYPE> *_insert_before(node<ITEM_TYPE> *&head, node<ITEM_TYPE> *before_this, ITEM_TYPE insert_this)
{
    // empty list -> just add it
    if (head == nullptr)
    {
        _insert_head(head, insert_this);
        return head;
    }

    // find the prev node
    node<ITEM_TYPE> *prev = _previous_node(head, before_this);

    // if prev is at the start
    if (prev == nullptr)
    {
        _insert_head(head, insert_this);
        return head;
    }
    // create the new node
    node<ITEM_TYPE> *temp = new node<ITEM_TYPE>(insert_this, before_this);
    prev->_next = temp;

    return temp;
}

// delete, return item
template <typename ITEM_TYPE>
ITEM_TYPE _delete_node(node<ITEM_TYPE> *&head, node<ITEM_TYPE> *delete_this)
{
    // find the previous node to delete_this
    node<ITEM_TYPE> *prev = _previous_node(head, delete_this);

    // if delete_this is at the start
    if (prev == nullptr)
        head = delete_this->_next;

    else
        prev->_next = delete_this->_next;

    ITEM_TYPE deleted = delete_this->_item;
    delete[] delete_this;
    return deleted;
}

// duplicate the list...
template <typename ITEM_TYPE>
node<ITEM_TYPE> *_copy_list(node<ITEM_TYPE> *head)
{

    node<ITEM_TYPE> *new_head = nullptr; // create a new list
    // if the src is empty
    if (head == nullptr)
        return new_head;

    node<ITEM_TYPE> *walker1 = head;     // walker for src head
    node<ITEM_TYPE> *walker2 = new_head; // walker for new_head

    // iterate through src list
    while (walker1 != nullptr)
    {
        // walker2 points to the last one assigned
        walker2 = _insert_after(new_head, walker2, walker1->_item);
        walker1 = walker1->_next;
    }

    return new_head;
}

// duplicate list and return the last node of the copy
template <typename T>
node<T> *_copy_list(node<T> *&dest, node<T> *src)
{
    node<T> *walker1 = src;  // walker for src
    node<T> *walker2 = dest; // walker for dest

    // iterate through src list
    while (walker1 != nullptr)
    {
        // walker2 points to the last one assigned
        walker2 = _insert_after(dest, walker2, walker1->_item);
        walker1 = walker1->_next;
    }

    // return the last node
    return walker2;
}

// delete all the nodes
template <typename ITEM_TYPE>
void _clear_list(node<ITEM_TYPE> *&head)
{
    node<ITEM_TYPE> *curr = head;

    while (curr != nullptr)
    {
        // to help delete
        node<ITEM_TYPE> *temp = curr;
        curr = curr->_next;
        delete temp;
    }

    head = nullptr;
}

//_item at this position
template <typename ITEM_TYPE>
ITEM_TYPE &_at(node<ITEM_TYPE> *head, int pos)
{
    node<ITEM_TYPE> *walker = head;
    for (int i = 0; i < pos; i++)
    {
        walker = walker->_next;
    }

    return walker->_item;
}

//. . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . .
//      Sorted List Routines. order: 0: ascending, order: other: descending
//                              Assume a Sorted List
//. . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . .

template <typename ITEM_TYPE>
node<ITEM_TYPE> *_insert_sorted(node<ITEM_TYPE> *&head, ITEM_TYPE item, bool ascending = true)
{

    node<ITEM_TYPE> *walker = head;
    while (item > walker->_item)
    {
        // if the item is largest
        if (walker->_next == nullptr)
            return _insert_after(head, walker, item);

        walker = walker->_next;
    }

    return _insert_before(head, walker, item);
}

// insert or add if a dup
template <typename ITEM_TYPE>
node<ITEM_TYPE> *_insert_sorted_and_add(node<ITEM_TYPE> *&head, ITEM_TYPE item, bool ascending = true)
{
    // search if the number is in the list
    node<ITEM_TYPE> *walker = _search_list(head, item);
    if (walker != nullptr)
        walker->_item *= 2; // found

    else
        _insert_sorted(head, item);
}

// node after which this item goes order: 0 ascending
template <typename ITEM_TYPE>
node<ITEM_TYPE> *_where_this_goes(node<ITEM_TYPE> *head, ITEM_TYPE item, bool ascending = true)
{
    node<ITEM_TYPE> *ptr = node<int>();
    return ptr;
}
// Last Node in the list
template <typename ITEM_TYPE>
node<ITEM_TYPE> *_last_node(node<ITEM_TYPE> *head)
{
    node<ITEM_TYPE> *ptr = node<int>();
    return ptr;
} // never use this function.

#endif
#ifndef LIST_SIMPLE_CPP
#define LIST_SIMPLE_CPP
#include "list_simple.h"

template <class ITEM_TYPE>
List<ITEM_TYPE>::List() : _size(0), head(nullptr)
{
}

// BIG THREE
template <class ITEM_TYPE>
List<ITEM_TYPE>::~List()
{
    _clear_list(head);
}

template <class ITEM_TYPE>
List<ITEM_TYPE>::List(const List<ITEM_TYPE> &copyThis)
{
    head = _copy_list(copyThis.head);
    _size = copyThis._size;
}

template <class ITEM_TYPE>
List<ITEM_TYPE> &List<ITEM_TYPE>::operator=(const List &RHS)
{
    // clear the list first
    _clear_list(head);
    head = _copy_list(RHS.head);
    _size = RHS._size;

    return *this;
}

template <class ITEM_TYPE>
node<ITEM_TYPE> *List<ITEM_TYPE>::insert_head(ITEM_TYPE i)
{
    _size++;
    return _insert_head(head, i);
} // inset i at the head of list

template <class ITEM_TYPE>
node<ITEM_TYPE> *List<ITEM_TYPE>::insert_after(ITEM_TYPE i, // insert i after iMarker
                                               node<ITEM_TYPE> *iMarker)
{
    _size++;
    return _insert_after(head, iMarker, i);
}

template <class ITEM_TYPE>
node<ITEM_TYPE> *List<ITEM_TYPE>::insert_before(ITEM_TYPE i, // insert i before iMarker
                                                node<ITEM_TYPE> *iMarker)
{
    _size++;
    return _insert_before(head, iMarker, i);
}

template <class ITEM_TYPE>
node<ITEM_TYPE> *List<ITEM_TYPE>::insert_sorted(ITEM_TYPE i)
{
    _size++;
    return _insert_sorted(head, i);
} // insert i. Assume sorted list

template <class ITEM_TYPE>
ITEM_TYPE List<ITEM_TYPE>::Delete(node<ITEM_TYPE> *iMarker)
{
    _size--;
    return _delete_node(head, iMarker);
} // delete node pointed to by iMarker

template <class ITEM_TYPE>
void List<ITEM_TYPE>::Print() const
{
    _print_list(head);
} // print the list

template <class ITEM_TYPE>
node<ITEM_TYPE> *List<ITEM_TYPE>::search(const ITEM_TYPE &key)
{
    return _search_list(head, key);
} // return pointer to node containing
  //   key. NULL if not there
template <class ITEM_TYPE>
node<ITEM_TYPE> *List<ITEM_TYPE>::prev(node<ITEM_TYPE> *iMarker)
{
    return _previous_node(head, iMarker);
} // get the previous node to iMarker

template <class ITEM_TYPE>
ITEM_TYPE &List<ITEM_TYPE>::operator[](int index)
{
    assert(_size && index < _size && index >= 0);
    return _at(head, index);
} // return the item at index

template <class ITEM_TYPE>
node<ITEM_TYPE> *List<ITEM_TYPE>::begin() const
{
    return head;
} // return the head of the list

template <class ITEM_TYPE>
node<ITEM_TYPE> *List<ITEM_TYPE>::end() const
{
    return nullptr;
}

template <class U>
ostream &operator<<(ostream &outs, // insertion operator for list
                    const List<U> &l)
{
    for (node<U> *walker = l.head; walker != nullptr; walker = walker->_next)
    {
        outs << *walker;
    }

    outs << "|||\n";
    return outs;
}

template <class ITEM_TYPE>
node<ITEM_TYPE> *List<ITEM_TYPE>::last_node() const
{
    node<ITEM_TYPE> *walker;
    for (walker = head; walker->_next != nullptr; walker = walker->_next)
    {
    }

    return walker;
}

#endif
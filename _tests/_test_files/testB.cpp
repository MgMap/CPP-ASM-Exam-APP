#include "gtest/gtest.h"
#include <iostream>
#include <iomanip>
#include "../../includes/list_simple/list_simple.h"
#include "../../includes/linked_list_functions/linked_list_functions.h"
#include "../../includes/node/node.h"

using namespace std;

// for testing
node<int> *make_list(int size = 5)
{
  int arr[20] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16, 17, 18, 19, 20};
  assert(size < 20);

  node<int> *head_ptr = nullptr;
  for (int i = size; i > 0; i--)
  {
    _insert_head(head_ptr, arr[i - 1]);
  }

  return head_ptr;
}

node<int> *make_list2(int size = 5)
{
  int arr[7] = {4, 9, 13, 22, 23, 24, 77};
  assert(size < 7);

  node<int> *head_ptr = nullptr;
  for (int i = size; i > 0; i--)
  {
    _insert_head(head_ptr, arr[i]);
  }

  return head_ptr;
}

bool test_node_insertion(bool debug = false)
{
  if (debug)
  {
    node<int> x = node<int>(3, nullptr);
    cout << x << endl;
  }

  return true;
}
bool test_insert_head(bool debug = false)
{

  if (debug)
  {
    node<int> *head_ptr = nullptr;
    for (int i = 0; i < 5; i++)
    {
      node<int> *inserted = _insert_head(head_ptr, i);
    }
    _print_list(head_ptr);
    cout << endl;
  }

  return true;
}
bool test_insert_after(bool debug = false)
{
  if (debug)
  {
    node<int> *inserted = nullptr;
    node<int> *head_ptr = nullptr;
    for (int i = 0; i < 5; i++)
    {
      _insert_head(head_ptr, i);
    }
    cout << "BEFORE insert_after 3: ";
    _print_list(head_ptr);
    cout << endl;

    node<int> *x = _search_list(head_ptr, 3);
    inserted = _insert_after(head_ptr, x, 77);

    cout << "Inserted: " << *inserted << endl;
    cout << "AFTER insert_after 3: ";
    _print_list(head_ptr);
    cout << endl;

    // double
    node<double> *head_ptr2 = nullptr;
    for (int i = 0; i < 5; i++)
    {
      _insert_head(head_ptr2, i * 1.1);
    }
    cout << "BEFORE insert_after 4.4: ";
    _print_list(head_ptr2);
    cout << endl;

    node<double> *z = _search_list(head_ptr2, 4.4);
    _insert_after(head_ptr2, z, 99.99);

    cout << "AFTER insert_after 4.4: ";
    _print_list(head_ptr2);
    cout << endl;

    // empty list
    node<int> *head_ptr3 = nullptr;
    cout << "BEFORE insert_after empty: ";
    _print_list(head_ptr3);
    cout << endl;
    _insert_after(head_ptr3, x, 3);
    cout << "AFTER insert_after empty: ";
    _print_list(head_ptr3);
    cout << endl;
  }

  return true;
}

bool test_previous_node(bool debug = false)
{
  if (debug)
  {
    // found in the mid
    node<int> *head_ptr = make_list(10);
    node<int> *found = _search_list(head_ptr, 7);
    node<int> *prev = _previous_node(head_ptr, found);
    _print_list(head_ptr);
    cout << "The previous node is " << *prev << endl;

    // found at the start
    found = _search_list(head_ptr, 1);
    prev = _previous_node(head_ptr, found);
    _print_list(head_ptr);
    cout << "The previous node is " << prev << endl;
  }

  return true;
}

bool test_delete_node(bool debug = false)
{
  if (debug)
  {
    // found in the mid
    node<int> *head_ptr = make_list(10);
    node<int> *found = _search_list(head_ptr, 7); // to delete 7
    cout << "Before deleting 7: " << endl;
    _print_list(head_ptr);

    int deleted = _delete_node(head_ptr, found);
    cout << deleted << " was deleted from the list" << endl;
    _print_list(head_ptr);

    // delete at the start
    found = _search_list(head_ptr, 1); // to delete 1
    cout << "Before deleting 1: " << endl;
    _print_list(head_ptr);

    deleted = _delete_node(head_ptr, found);
    cout << deleted << " was deleted from the list" << endl;
    _print_list(head_ptr);
  }

  return true;
}

bool test_insert_before(bool debug = false)
{
  if (debug)
  {
    // found in the mid
    node<int> *head_ptr = make_list(10);
    node<int> *found = _search_list(head_ptr, 7);
    cout << "Before inserting 999: ";
    _print_list(head_ptr);

    node<int> *inserted = _insert_before(head_ptr, found, 999);
    cout << *inserted << " was inserted\n";
    _print_list(head_ptr);

    // found at the start
    found = _search_list(head_ptr, 1);
    cout << "Before inserting 888: ";
    _print_list(head_ptr);

    inserted = _insert_before(head_ptr, found, 888);
    cout << *inserted << " was inserted\n";
    _print_list(head_ptr);
  }
  return true;
}

bool test_copy_list(bool debug = false)
{

  if (debug)
  {

    node<int> *head_ptr = make_list(17);
    node<int> *copy = _copy_list(head_ptr);
    cout << "Original: ";
    _print_list(head_ptr);
    cout << "Copy: ";
    _print_list(copy);
    cout << endl;

    // copy one node
    head_ptr = make_list(1);
    copy = _copy_list(head_ptr);
    cout << "Original: ";
    _print_list(head_ptr);
    cout << "Copy: ";
    _print_list(copy);
    cout << endl;

    // copy an empty node
    head_ptr = nullptr;
    copy = _copy_list(head_ptr);
    cout << "Original: ";
    _print_list(head_ptr);
    cout << "Copy: ";
    _print_list(copy);
    cout << endl;
  }

  return true;
}

bool test_copy_list2(bool debug = false)
{

  if (debug)
  {

    node<int> *head_ptr = make_list(17);
    node<int> *dest_ptr = nullptr;
    node<int> *last = _copy_list(dest_ptr, head_ptr);
    cout << "Original: ";
    _print_list(head_ptr);
    cout << "Copy: ";
    _print_list(dest_ptr);
    cout << "The last element copied is " << *last;
    cout << endl;

    node<int> *dest_ptr2 = nullptr;
    head_ptr = make_list(1);
    last = _copy_list(dest_ptr2, head_ptr);
    cout << "Original: ";
    _print_list(head_ptr);
    cout << "Copy: ";
    _print_list(dest_ptr2);
    cout << "The last element copied is " << *last;
    cout << endl;

    // copy an empty node
    head_ptr = nullptr;
    dest_ptr = _copy_list(head_ptr);
    cout << "Original: ";
    _print_list(head_ptr);
    cout << "Copy: ";
    _print_list(dest_ptr);
    cout << endl;
    _insert_before(dest_ptr, dest_ptr, 99);
    cout << "Copy after adding 99: ";
    _print_list(dest_ptr);
  }

  return true;
}

bool test_print_list_backwards(bool debug = false)
{

  if (debug)
  {

    node<int> *head_ptr = make_list(17);
    cout << "original: ";
    _print_list(head_ptr);
    cout << "backwards: ";
    _print_list_backwards(head_ptr);
    cout << endl;

    node<int> *head_ptr2 = nullptr;
    cout << "original: ";
    _print_list(head_ptr2);
    cout << "backwards: ";
    _print_list_backwards(head_ptr2);
    cout << endl;

    node<int> *head_ptr3 = make_list(1);
    cout << "original: ";
    _print_list(head_ptr3);
    cout << "backwards: ";
    _print_list_backwards(head_ptr3);
    cout << endl;
  }

  return true;
}

bool test_insert_sorted(bool debug = false)
{
  if (debug)
  {
    // found in the mid
    node<int> *head_ptr = make_list2(6);

    cout << "Before inserting 21: ";
    _print_list(head_ptr);

    node<int> *inserted = _insert_sorted(head_ptr, 21);
    cout << *inserted << " was inserted\n";
    _print_list(head_ptr);

    cout << "Before inserting 8: ";
    _print_list(head_ptr);

    inserted = _insert_sorted(head_ptr, 8);
    cout << *inserted << " was inserted\n";
    _print_list(head_ptr);

    cout << "Before inserting 99: ";
    _print_list(head_ptr);

    inserted = _insert_sorted(head_ptr, 99);
    cout << *inserted << " was inserted\n";
    _print_list(head_ptr);
  }
  return true;
}

TEST(TEST_STUB, TestNodeInsertion)
{

  EXPECT_EQ(1, test_node_insertion(false));
}

TEST(TEST_STUB, TestInsertHead)
{

  EXPECT_EQ(1, test_insert_head(false));
}

TEST(TEST_STUB, TestInsertAfter)
{

  EXPECT_EQ(1, test_insert_after(true));
}

TEST(TEST_STUB, TestPreviousNode)
{

  EXPECT_EQ(1, test_previous_node(false));
}
TEST(TEST_STUB, TestDeleteNode)
{

  EXPECT_EQ(1, test_delete_node(false));
}

TEST(TEST_STUB, TestInsertBefore)
{

  EXPECT_EQ(1, test_insert_before(false));
}

TEST(TEST_STUB, TestCopyList)
{

  EXPECT_EQ(1, test_copy_list(false));
}

TEST(TEST_STUB, TestCopyList2)
{

  EXPECT_EQ(1, test_copy_list2(false));
}

TEST(TEST_STUB, TestPrintBackwards)
{

  EXPECT_EQ(1, test_print_list_backwards(false));
}

TEST(TEST_STUB, TestInsertSorted)
{

  EXPECT_EQ(1, test_insert_sorted(false));
}

int main(int argc, char **argv)
{
  ::testing::InitGoogleTest(&argc, argv);
  std::cout << "\n\n----------running testB.cpp---------\n\n"
            << std::endl;
  return RUN_ALL_TESTS();
}
#include "gtest/gtest.h"
#include "stdio.h"
#include "errno.h"
#include "math.h"
#include "stdlib.h"
#include <iostream>

using namespace std;

extern "C" int addTwoValues(int, int);

// I never call this
extern "C" int OnlyToGetThingsINeedImported()
{
  printf("test\n");
  printf("%d", errno);
  double sine = sin(3.1415926535L / 6);
  void *Ptr = malloc(256);
  free(Ptr);

  return 0;
}

bool stub(bool debug = false)
{
  return true;
}

bool test_addTwoValues(bool debug = false)
{
  int num1 = 12;
  int num2 = 7;

  // call add two values from assembly
  int result = addTwoValues(num1, num2);
  if (result != num1 + num2)
  {

    cout << "The sum of " << num1 << " and " << num2 << " should be " << num1 + num2 << " but got " << result << " instead\n";

    return false;
  }

  return true;
}

//----- ----- ----- ----- ----- ----- ----- ----- ----- -----
// Lord is with me!
bool debug = false;
//----- ----- ----- ----- ----- ----- ----- ----- ----- -----

TEST(TEST_AddTwoValues, TestAddTwoValues)
{
  bool success = test_addTwoValues(debug);
  EXPECT_EQ(success, true);
}

int main(int argc, char **argv)
{
  if (argc > 1)
  {
    debug = argv[1][0] == 't';
  }
  ::testing::InitGoogleTest(&argc, argv);
  std::cout << "\n\n----------running basic_test.cpp---------\n\n"
            << std::endl;
  return RUN_ALL_TESTS();
}

#include "gtest/gtest.h"
#include <math.h>
#include <iostream>
#include <iomanip>
#include "../../includes/poly/poly.h"
#include "../../includes/array_functions/array_functions.h"
using namespace std;

bool test_term_operators(bool debug = false)
{
  // also test for CTORs
  Term t1(3.0, 2);
  Term t2(4.0, 2);

  Term t3(0, 2);
  t3 = t1 + t2;
  if (!compare_double(t3._coef, 7.0))
  {
    cout << "Term operator + not working\n";
    return false;
  }

  t3 = t1 - t2;
  if (!compare_double(t3._coef, -1.0))
  {
    cout << "Term operator - not working\n";
    return false;
  }

  t3 = t1 * t2;
  if (!compare_double(t3._coef, 12.0))
  {
    cout << "Term operator * not working\n";
    return false;
  }

  t3 = t1 / t2;
  if (!compare_double(t3._coef, 0.75))
  {
    cout << "Term operator / not working\n";
    return false;
  }

  t3 = -t1;
  if (!compare_double(t3._coef, -3.0))
  {
    cout << "Term unary operator - not working\n";
    return false;
  }

  if (!(t3 != t2))
  {
    cout << "Term operator != not working\n";
    return false;
  }

  t3 = t2;
  if (!(t3 == t2))
  {
    cout << "Term operator == not working\n";
    return false;
  }

  if (debug)
  {
    cout << "t1: " << t1 << endl;
    cout << "t2: " << t2 << endl;
    cout << "t1 + t2: " << t1 + t2 << endl;
    cout << "t1 - t2: " << t1 - t2 << endl;
    cout << "t1 * t2: " << t1 * t2 << endl;
    cout << "t1 / t2: " << t1 / t2 << endl;
    cout << "t3: " << t3 << endl;

    Term t4(3.0, 2);
    Term t5(3.0, 2);
    cout << "t4 - t5 = " << t4 - t5 << endl;
  }

  return true;
}

bool test_poly_CTORS(bool debug = false)
{
  double coefs1[] = {8.0, 5.0, 6.0, 0.0, 4.0};
  double coefs2[] = {2.0, 7.0, -3.0, 0.0, 1.0, 9.0};
  double coefs3[] = {0.0, 8.0, 1.0, 5.0};

  Poly p;
  Poly p1(coefs1, 4);
  Poly p2(coefs2, 5);
  Poly p3(coefs3, 3);

  if (p.order() != 0 || p[0]._coef != 0 || p[0]._exp != 0)
  {
    cout << "One Argument CTOR not working.\n";
    return false;
  }
  if (p1.order() != 4 || p1[1]._coef != 5.0 || p1[1]._exp != 1)
  {
    cout << "Two Argument CTOR not working.\n";
    return false;
  }

  if (debug)
  {
    cout << "p: " << p << endl;
    cout << "p1: " << p1 << endl;
    cout << "p2: " << p2 << endl;
    cout << "p3: " << p3 << endl;
  }

  return true;
}

bool test_big_three(bool debug = false)
{
  double coefs1[] = {8.0, 5.0, 6.0, 0.0, 4.0};
  Poly p1(coefs1, 4);
  Poly p2(p1);

  if (p2.order() != 4 || p2[1]._coef != 5.0 || p2[1]._exp != 1)
  {
    cout << "Copy CTOR not working.\n";
    return false;
  }

  double coefs3[] = {0.0, 8.0, 1.0, 5.0};
  Poly p3(coefs3, 3);

  p2 = p3;
  if (p2.order() != 3 || p2[3]._coef != 5.0 || p2[2]._exp != 2)
  {
    cout << "Assignment Operator not working.\n";
    return false;
  }

  if (debug)
  {
    cout << "p1: " << p1 << endl;
    cout << "p2: " << p2 << endl;
  }

  return true;
}

bool test_poly_equality(bool debug = false)
{

  double coefs1[] = {8.0, 5.0, 6.0, 0.0, 4.0};
  Poly p1(coefs1, 4);
  Poly p2(p1);

  double coefs3[] = {0.0, 8.0, 1.0, 5.0};
  Poly p3(coefs3, 3);

  if (!(p1 == p2))
  {
    cout << "Equality operator not working\n";
    return false;
  }
  if (p1 == p3)
  {
    cout << "Equality operator not working\n";
    return false;
  }

  if (!(p1 != p3))
  {
    cout << "Inequality operator not working\n";
    return false;
  }

  return true;
}

bool test_poly_greater(bool debug = false)
{
  double coefs1[] = {4.0, 3.0, 13.0};
  Poly p1(coefs1, 2);
  double coefs2[] = {1.0, 3.0, 13.0};
  Poly p2(coefs2, 2);

  if (!(p1 > p2))
  {
    cout << "Greater than operator not working\n";
    return false;
  }

  double coefs3[] = {4.0, 3.0, 13.0, 1.0};
  Poly p3(coefs3, 3);

  if (!(p3 > p2))
  {
    cout << "Greater than operator not working\n";
    return false;
  }

  double coefs4[] = {4.0, 3.0, 13.0, 1.0};
  Poly p4(coefs4, 3);
  if (p3 > p4)
  {
    cout << "Greater than operator not working\n";
    return false;
  }

  return true;
}

bool test_poly_lesser(bool debug = false)
{
  double coefs1[] = {4.0, 3.0, 13.0};
  Poly p1(coefs1, 2);
  double coefs2[] = {1.0, 3.0, 13.0};
  Poly p2(coefs2, 2);

  if (p1 < p2)
  {
    cout << "Lesser than operator not working\n";
    return false;
  }

  double coefs3[] = {4.0, 3.0, 13.0, 1.0};
  Poly p3(coefs3, 3);

  if (p3 < p2)
  {
    cout << "Lesser than operator not working\n";
    return false;
  }

  double coefs4[] = {4.0, 3.0, 13.0, 1.0};
  Poly p4(coefs4, 3);
  if (!(p3 < p4))
  {
    cout << "Lesser than operator not working\n";
    return false;
  }

  return true;
}

// major arithmetic operators
void test_plus(const Poly &p, const Poly &q)
{
  Poly r = p + q;
  cout << p << " + " << q << endl;
  cout << "      = " << r;

  // if r = p + q then r - q should be equal to p:
  if (r - q == p)
  {
    cout << "VERIFIED" << endl;
  }
  else
  {
    cout << endl
         << "   ***VERIFICATION FAILED" << endl;
    cout << "   r - q: " << r - q << endl;
    cout << "   r - q: " << r - q << "=/=" << p << endl;
  }
}

void test_minus(const Poly &p, const Poly &q)
{
  Poly r = p - q;
  cout << p << " - " << q << endl;
  cout << "      = " << r;

  // if r = p - q then p should be equal to r + q:
  if (r + q == p)
  {
    cout << "VERIFIED" << endl;
  }
  else
  {
    cout << endl
         << "   ***VERIFICATION FAILED" << endl;
    cout << "   r + q: " << r + q << endl;
    cout << "   r + q: " << r + q << "=/=" << p << endl;
  }
}

void test_multiply(const Poly &p, const Poly &q)
{
  Poly r = p * q;
  cout << p << " * " << q << endl;
  cout << "      = " << r;

  // if r = p * q then p should be equal to r / q:
  if (r / q == p)
  {
    cout << "VERIFIED" << endl;
  }
  else
  {
    cout << endl
         << "   ***VERIFICATION FAILED" << endl;
    cout << "   r / q: " << r / q << endl;
    cout << "   r / q: " << r / q << "=/=" << p << endl;
  }
}

void test_division(const Poly &p, const Poly &q)
{
  Poly r = p / q;
  Poly rem = p % q;
  cout << p << " / " << q << endl;
  cout << "      = " << r << "   rem = " << rem;

  // if r = p / q then r * q + p % q should be equal to p:
  if (r * q + p % q == p)
  {
    cout << "VERIFIED" << endl;
  }
  else
  {
    cout << endl
         << "   ***VERIFICATION FAILED" << endl;
    cout << "   r * q: " << r * q << endl;
    cout << "   p % q: " << p % q << endl;
    cout << "   r * q + p % q: " << r * q + p % q << "=/=" << p << endl;
  }
}

void print_operation(char p, char q, char sign)
{
  cout << "\n------- " << p << " " << sign << " " << q << " ----------------------\n";
}

bool test_operator_add(bool debug = false)
{
  double coefs1[] = {8.0, 5.0, 6.0, 0.0, 4.0};
  double coefs2[] = {2.0, 7.0, 3.0, 0.0, 1.0, 9.0};
  Poly p(coefs1, 4);
  Poly q(coefs2, 5);

  Poly r = p + q;
  cout << "p: " << p << endl;
  cout << "q: " << q << endl;
  cout << "r: " << r << endl;
  cout << "r.order: " << r.order() << endl;
  return true;
}

bool test_operator_divide(bool debug = false)
{
  // P: [+2.0X^12 ]
  // Q: [+3.0X^8 ]
  double coefs1[] = {4.0};
  double coefs2[] = {2.0};
  Poly p(coefs1, 0);
  Poly q(coefs2, 0);

  Poly r = p / q;
  cout << "p: " << p << endl;
  cout << "q: " << q << endl;
  cout << "r = p / q : " << r << endl;
  cout << "r.order: " << r.order() << endl;

  r = q / p;
  cout << "r = q / p : " << r << endl;
  cout << "r.order: " << r.order() << endl;
  return true;
}

bool test_major_operators(bool debug = false)
{
  cout << "\n\n\n";

  // P: [+3.0X^3 +2.0X^2 +X +5.0 ]
  // Q: [+4.0X^4 +3.0X^3 +2.0X^2 +X +5.0 ]
  double coefs_p1[] = {5.0, 1.0, 2.0, 3.0};
  double coefs_q1[] = {5.0, 1.0, 2.0, 3.0, 4.0};
  Poly p1(coefs_p1, 3);
  Poly q1(coefs_q1, 4);

  cout << "P1: " << p1 << endl;
  cout << "Q1: " << q1 << endl;
  //+
  print_operation('p', 'q', '+');
  test_plus(p1, q1);
  print_operation('q', 'p', '+');
  test_plus(q1, p1);
  //-
  print_operation('p', 'q', '-');
  test_minus(p1, q1);
  print_operation('q', 'p', '-');
  test_minus(q1, p1);
  //*
  print_operation('p', 'q', '*');
  test_multiply(p1, q1);
  print_operation('q', 'p', '*');
  test_multiply(q1, p1);
  // div
  print_operation('p', 'q', '/');
  test_division(p1, q1);
  print_operation('q', 'p', '/');
  test_division(q1, p1);

  // for additional testing
  double coefs3[] = {-2.0, 1.0, 1.0};
  double coefs4[] = {-1.0, 1.0};
  Poly p3(coefs3, 2);
  Poly p4(coefs4, 1);
  // cout << "p3: " << p3 << endl;
  // cout << "p4: " << p4 << endl;
  test_division(p3, p4);

  cout << "--------------------------------------------------\n";
  double coefs5[] = {3.0, -2.0, 0.0, 4.0, 0.0, 6.0};
  double coefs6[] = {5.0, 1, 2.0, 3.0, 4.0};
  Poly p5(coefs5, 5);
  Poly p6(coefs6, 4);
  test_plus(p5, p6);
  test_minus(p5, p6);
  test_multiply(p5, p6);
  test_division(p5, p6);

  // test with zero
  Poly p7;

  test_plus(p5, p7);
  test_minus(p5, p7);
  test_multiply(p7, p5);

  Poly p8;
  test_minus(p7, p8);
  test_minus(p8, p7);
  double coefs9[] = {0.0, 0, 0.0, 0.0, 0.0};
  Poly p9(coefs9, 4);
  cout << "p9: " << p9 << endl;
  cout << "p9.order: " << p9.order() << endl;
  double *tempor = p9.get_coefs();
  cout << "p9._coefs[0]: " << *tempor << endl;

  p5 = p5;
  cout << "p5: " << p5 << endl;

  return true;
}

bool test_extraction(bool debug = false)
{

  Poly p, q;
  cout << "p: ";
  cin >> p;
  cout << "q: ";
  cin >> q;
  cout << "P is " << p << endl;
  cout << "Q is " << q << endl;

  return true;
}

TEST(TEST_STUB, TestTermOperators)
{

  EXPECT_EQ(1, test_term_operators(false));
}

TEST(TEST_STUB, TestPolyCTORS)
{

  EXPECT_EQ(1, test_poly_CTORS(false));
}

TEST(TEST_STUB, TestBigThree)
{

  EXPECT_EQ(1, test_big_three(false));
}

TEST(TEST_STUB, TestPolyEquality)
{

  EXPECT_EQ(1, test_poly_equality(false));
}

TEST(TEST_STUB, TestPolyGreater)
{

  EXPECT_EQ(1, test_poly_greater(false));
}

TEST(TEST_STUB, TestPolyLesser)
{

  EXPECT_EQ(1, test_poly_lesser(false));
}

TEST(TEST_STUB, TestOperatorAdd)
{

  EXPECT_EQ(1, test_operator_add(false));
}
TEST(TEST_STUB, TestOperatorDivide)
{

  EXPECT_EQ(1, test_operator_divide(false));
}

TEST(TEST_STUB, TestMajorOperators)
{

  // EXPECT_EQ(1, test_major_operators(false));
}

TEST(TEST_STUB, TestExtraction)
{

  // EXPECT_EQ(1, test_extraction(false));
}

int main(int argc, char **argv)
{
  ::testing::InitGoogleTest(&argc, argv);
  std::cout << "\n\n----------running testB.cpp---------\n\n"
            << std::endl;
  return RUN_ALL_TESTS();
}

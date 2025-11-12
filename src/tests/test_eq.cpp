#include "test.h"

TEST(EqMatrix, Subtest_1) {
  S21Matrix a(2, 2);
  S21Matrix b(a);
  ASSERT_TRUE(a.EqMatrix(b));
}

TEST(EqMatrix, Subtest_2) {
  S21Matrix a(2, 2);
  S21Matrix b(3, 2);
  ASSERT_FALSE(a.EqMatrix(b));
}

TEST(EqMatrix, Subtest_3) {
  S21Matrix a(2, 2);
  a.editElem(1, 1) = 10;
  S21Matrix b(a);
  ASSERT_TRUE(a.EqMatrix(b));
}

TEST(EqMatrix, Subtest_4) {
  S21Matrix a(2, 2);
  a.editElem(1, 1) = 10;
  S21Matrix b(2, 2);
  ASSERT_FALSE(a.EqMatrix(b));
}

TEST(EqMatrix, Subtest_5) {
  S21Matrix a(2, 2);
  a.editElem(1, 1) = 10;
  S21Matrix b(2, 2);
  ASSERT_FALSE(a.EqMatrix(b));
}
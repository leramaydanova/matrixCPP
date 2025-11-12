#include "test.h"

TEST(Operators, Copy) {
  S21Matrix a(3, 3);
  S21Matrix b;
  b = a;
  ASSERT_EQ(b.getCols(), a.getCols());
  ASSERT_EQ(b.getRows(), a.getRows());
  ASSERT_EQ(b.getMatrix(), a.getMatrix());
}

TEST(Operators, Plus) {
  S21Matrix a(3, 3);
  S21Matrix b(3, 3);
  a.editElem(2, 2) = 33;
  S21Matrix res = b + a;
  ASSERT_TRUE(res(2, 2) == 33);
}

TEST(Operators, Minus) {
  S21Matrix a(3, 3);
  S21Matrix b(3, 3);
  a.editElem(2, 2) = 33;
  S21Matrix res = b - a;
  ASSERT_TRUE(res(2, 2) == -33);
}

TEST(Operators, MulMatrix) {
  S21Matrix a(2, 2);
  S21Matrix b(2, 2);
  a.editElem(0, 0) = 4;
  a.editElem(0, 1) = 2;
  a.editElem(1, 0) = 9;
  a.editElem(1, 1) = 0;

  b.editElem(0, 0) = 3;
  b.editElem(0, 1) = 1;
  b.editElem(1, 0) = -3;
  b.editElem(1, 1) = 4;
  S21Matrix res = a * b;
  EXPECT_DOUBLE_EQ(res(0, 0), 6);
  EXPECT_DOUBLE_EQ(res(0, 1), 12);
  EXPECT_DOUBLE_EQ(res(1, 0), 27);
  EXPECT_DOUBLE_EQ(res(1, 1), 9);
}

TEST(Operators, MulNumber) {
  S21Matrix a(3, 10);
  a.editElem(1, 1) = 3;

  S21Matrix res = a * 4;
  EXPECT_DOUBLE_EQ(res(1, 1), 12);
}

TEST(Operators, Eq) {
  S21Matrix a(2, 2);
  a.editElem(1, 1) = 10;
  S21Matrix b(a);
  bool res = a == b;
  ASSERT_TRUE(res);
}

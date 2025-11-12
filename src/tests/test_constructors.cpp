#include "test.h"

TEST(Constructors, InitDefault) {
  S21Matrix a;
  EXPECT_EQ(a.getRows(), 0);
  EXPECT_EQ(a.getCols(), 0);
  ASSERT_TRUE(a.getMatrix().empty());
}

TEST(Constructors, InitParams) {
  S21Matrix a(3, 10);
  EXPECT_EQ(a.getRows(), 3);
  EXPECT_EQ(a.getCols(), 10);
  ASSERT_FALSE(a.getMatrix().empty());
  EXPECT_EQ(a(0, 0), 0);
}

TEST(Constructors, InitNegParams) {
  ASSERT_THROW(S21Matrix(-1, 0), std::invalid_argument);
}

TEST(Constructors, Copy) {
  S21Matrix a(3, 10);
  S21Matrix b(a);
  ASSERT_TRUE(a.EqMatrix(b));
}

TEST(Constructors, Move) {
  S21Matrix a(3, 10);
  S21Matrix b(std::move(a));
  ASSERT_FALSE(a.EqMatrix(b));
  EXPECT_EQ(a.getRows(), 0);
  EXPECT_EQ(a.getCols(), 0);
  ASSERT_TRUE(a.getMatrix().empty());
}

TEST(Constructors, Destruct) {
  S21Matrix *ptr;
  {
    S21Matrix a(3, 3);
    ptr = &a;
    ptr->editElem(1, 1) = 10;
    EXPECT_EQ(ptr->getRows(), 3);
    EXPECT_EQ(ptr->getCols(), 3);
  }
  EXPECT_EQ(ptr->getRows(), 0);
  EXPECT_EQ(ptr->getCols(), 0);
  ASSERT_TRUE(ptr->getMatrix().empty());
}
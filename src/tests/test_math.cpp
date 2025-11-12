#include "test.h"

TEST(MathFunctions, SumMatrix_1) {
  S21Matrix a(3, 10);
  a.editElem(1, 1) = 3;
  S21Matrix b(a);
  a += b;
  EXPECT_DOUBLE_EQ(a(1, 1), 6);
}

TEST(MathFunctions, SumMatrix_2) {
  S21Matrix a(3, 10);
  S21Matrix b(10, 10);
  ASSERT_THROW(a += b, std::invalid_argument);
}

TEST(MathFunctions, SubMatrix_1) {
  S21Matrix a(3, 10);
  a.editElem(1, 1) = 3;
  S21Matrix b(a);
  a -= b;
  EXPECT_DOUBLE_EQ(a(1, 1), 0);
}

TEST(MathFunctions, SubMatrix_2) {
  S21Matrix a(3, 10);
  S21Matrix b(10, 10);
  ASSERT_THROW(a -= b, std::invalid_argument);
}

TEST(MathFunctions, MulNumber) {
  S21Matrix a(3, 10);
  a.editElem(1, 1) = 3;
  a *= 4;
  EXPECT_DOUBLE_EQ(a(1, 1), 12);
}

TEST(MathFunctions, MulMatrix_1) {
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
  a *= b;
  EXPECT_DOUBLE_EQ(a(0, 0), 6);
  EXPECT_DOUBLE_EQ(a(0, 1), 12);
  EXPECT_DOUBLE_EQ(a(1, 0), 27);
  EXPECT_DOUBLE_EQ(a(1, 1), 9);
}

TEST(MathFunctions, MulMatrix_2) {
  S21Matrix a(2, 3);
  S21Matrix b(2, 2);
  ASSERT_THROW(a *= b, std::invalid_argument);
}

TEST(MathFunctions, Transpose_1) {
  S21Matrix a(3, 3);
  a.editElem(0, 0) = 5;
  a.editElem(0, 1) = 7;
  a.editElem(0, 2) = 1;
  a.editElem(1, 0) = -4;
  a.editElem(1, 1) = 1;
  a.editElem(1, 2) = 0;
  a.editElem(2, 0) = 2;
  a.editElem(2, 1) = 0;
  a.editElem(2, 2) = 3;
  S21Matrix res = a.Transpose();
  for (int i{}; i < 3; ++i) {
    for (int j{}; j < 3; ++j) {
      ASSERT_TRUE(res(j, i) == a(i, j));
    }
  }
}

TEST(MathFunctions, Transpose_2) {
  S21Matrix a;
  S21Matrix res = a.Transpose();
  ASSERT_TRUE(res.getRows() == 0);
  ASSERT_TRUE(res.getCols() == 0);
  ASSERT_TRUE(res.getMatrix().empty());
}

TEST(MathFunctions, CalcComplements_1) {
  S21Matrix a(2, 3);
  ASSERT_THROW(a.CalcComplements(), std::invalid_argument);
}

TEST(MathFunctions, CalcComplements_2) {
  S21Matrix a(3, 3);
  a.editElem(0, 0) = 5;
  a.editElem(0, 1) = 7;
  a.editElem(0, 2) = 1;
  a.editElem(1, 0) = -4;
  a.editElem(1, 1) = 1;
  a.editElem(1, 2) = 0;
  a.editElem(2, 0) = 2;
  a.editElem(2, 1) = 0;
  a.editElem(2, 2) = 3;
  S21Matrix res = a.CalcComplements();
  EXPECT_DOUBLE_EQ(res(0, 0), 3);
  EXPECT_DOUBLE_EQ(res(0, 1), 12);
  EXPECT_DOUBLE_EQ(res(0, 2), -2);
  EXPECT_DOUBLE_EQ(res(1, 0), -21);
  EXPECT_DOUBLE_EQ(res(1, 1), 13);
  EXPECT_DOUBLE_EQ(res(1, 2), 14);
  EXPECT_DOUBLE_EQ(res(2, 0), -1);
  EXPECT_DOUBLE_EQ(res(2, 1), -4);
  EXPECT_DOUBLE_EQ(res(2, 2), 33);
}

TEST(MathFunctions, Determinant_1) {
  S21Matrix a(3, 3);
  a.editElem(0, 0) = 5;
  a.editElem(0, 1) = 7;
  a.editElem(0, 2) = 1;
  a.editElem(1, 0) = -4;
  a.editElem(1, 1) = 1;
  a.editElem(1, 2) = 0;
  a.editElem(2, 0) = 2;
  a.editElem(2, 1) = 0;
  a.editElem(2, 2) = 3;
  double res = a.Determinant();
  EXPECT_DOUBLE_EQ(res, 97);
}

TEST(MathFunctions, Determinant_2) {
  S21Matrix a(2, 3);
  ASSERT_THROW(a.Determinant(), std::logic_error);
}

TEST(MathFunctions, Determinant_3) {
  S21Matrix a(2, 2);
  a.editElem(0, 0) = 5;
  a.editElem(0, 1) = 7;
  a.editElem(1, 0) = -4;
  a.editElem(1, 1) = 1;
  EXPECT_DOUBLE_EQ(a.Determinant(), 33);
}

TEST(MathFunctions, Determinant_4) {
  S21Matrix a(1, 1);
  a.editElem(0, 0) = 5;
  EXPECT_DOUBLE_EQ(a.Determinant(), 5);
}

TEST(MathFunctions, InverseMatrix_1) {
  S21Matrix a(2, 2);
  a.editElem(0, 0) = 3;
  a.editElem(0, 1) = 4;
  a.editElem(1, 0) = 1;
  a.editElem(1, 1) = 2;
  S21Matrix res = a.InverseMatrix();

  ASSERT_TRUE(res(0, 0) == 1);
  ASSERT_TRUE(res(0, 1) == -2);
  ASSERT_TRUE(res(1, 0) == -0.5);
  ASSERT_TRUE(res(1, 1) == 1.5);
}

TEST(MathFunctions, InverseMatrix_2) {
  S21Matrix a(1, 1);
  a.editElem(0, 0) = 2;
  S21Matrix res = a.InverseMatrix();

  ASSERT_TRUE(res(0, 0) == 0.5);
}

TEST(MathFunctions, InverseMatrix_3) {
  S21Matrix a(1, 1);
  a.editElem(0, 0) = 2;
  S21Matrix res = a.InverseMatrix();

  ASSERT_TRUE(res(0, 0) == 0.5);
}

TEST(MathFunctions, InverseMatrix_4) {
  S21Matrix a(3, 3);
  a.editElem(0, 0) = 2;
  a.editElem(0, 1) = 5;
  a.editElem(0, 2) = 7;
  a.editElem(1, 0) = 6;
  a.editElem(1, 1) = 3;
  a.editElem(1, 2) = 4;
  a.editElem(2, 0) = 5;
  a.editElem(2, 1) = -2;
  a.editElem(2, 2) = -3;
  S21Matrix res = a.InverseMatrix();

  ASSERT_TRUE(res(0, 0) == 1);
  ASSERT_TRUE(res(0, 1) == -1);
  ASSERT_TRUE(res(0, 2) == 1);
  ASSERT_TRUE(res(1, 0) == -38);
  ASSERT_TRUE(res(1, 1) == 41);
  ASSERT_TRUE(res(1, 2) == -34);
  ASSERT_TRUE(res(2, 0) == 27);
  ASSERT_TRUE(res(2, 1) == -29);
  ASSERT_TRUE(res(2, 2) == 24);
}

TEST(MathFunctions, InverseMatrix_5) {
  S21Matrix a(3, 3);
  ASSERT_THROW(a.InverseMatrix(), std::logic_error);
}
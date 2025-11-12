#ifndef S21_MATRIX_H
#define S21_MATRIX_H

#include <iostream>
#include <vector>

class S21Matrix {
  using matrix = std::vector<std::vector<double>>;

 private:
  int rows_, cols_;
  matrix matrix_;

 public:
  S21Matrix() noexcept;
  S21Matrix(int rows, int cols);
  S21Matrix(const S21Matrix &other) noexcept;
  S21Matrix(S21Matrix &&other) noexcept;
  ~S21Matrix() noexcept;

  bool EqMatrix(const S21Matrix &other) noexcept;
  void SumMatrix(const S21Matrix &other);
  void SubMatrix(const S21Matrix &other);
  void MulNumber(const double num) noexcept;
  void MulMatrix(const S21Matrix &other);
  S21Matrix Transpose();
  S21Matrix CalcComplements();
  double Determinant();
  S21Matrix GetMinorMatrix(int row, int col);
  S21Matrix InverseMatrix();

  S21Matrix operator+(const S21Matrix &other);
  S21Matrix operator-(const S21Matrix &other);
  S21Matrix operator*(const S21Matrix &other);
  S21Matrix operator*(double num) noexcept;
  bool operator==(const S21Matrix &other);
  S21Matrix &operator=(S21Matrix &other) noexcept;
  S21Matrix &operator=(S21Matrix &&other) noexcept;
  S21Matrix &operator+=(const S21Matrix &other);
  S21Matrix &operator-=(const S21Matrix &other);
  S21Matrix &operator*=(const S21Matrix &other);
  S21Matrix &operator*=(double num) noexcept;
  double operator()(int i, int j);

  int getRows() noexcept;
  int getCols() noexcept;
  matrix getMatrix() noexcept;

  int &editRows() noexcept;
  int &editCols() noexcept;
  double &editElem(int i, int j);
};

#endif
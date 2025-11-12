#include "s21_matrix_oop.h"

S21Matrix &S21Matrix::operator=(S21Matrix &&other) noexcept {
  if (this != &other) {
    matrix_ = std::move(other.matrix_);
    rows_ = other.rows_;
    cols_ = other.cols_;
    other.rows_ = 0;
    other.cols_ = 0;
  }
  return *this;
}

S21Matrix &S21Matrix::operator=(S21Matrix &other) noexcept {
  if (this != &other) {
    matrix_ = other.matrix_;
    rows_ = other.rows_;
    cols_ = other.cols_;
  }
  return *this;
}

S21Matrix S21Matrix::operator+(const S21Matrix &other) {
  if (rows_ != other.rows_ || cols_ != other.cols_) {
    throw std::exception();
  }

  S21Matrix res(rows_, cols_);
  for (int i{0}; i < rows_; ++i) {
    for (int j{0}; j < cols_; ++j) {
      res.matrix_[i][j] = matrix_[i][j] + other.matrix_[i][j];
    }
  }

  return res;
}

S21Matrix S21Matrix::operator-(const S21Matrix &other) {
  if (rows_ != other.rows_ || cols_ != other.cols_) {
    throw std::exception();
  }

  S21Matrix res(rows_, cols_);
  for (int i{0}; i < rows_; ++i) {
    for (int j{0}; j < cols_; ++j) {
      res.matrix_[i][j] = matrix_[i][j] - other.matrix_[i][j];
    }
  }

  return res;
}

S21Matrix S21Matrix::operator*(const S21Matrix &other) {
  if (cols_ != other.rows_) {
    throw std::exception();
  }

  S21Matrix res(rows_, other.cols_);
  for (int i{0}; i < rows_; i++) {
    for (int j{0}; j < other.cols_; j++) {
      for (int n{0}; n < cols_; n++) {
        res.matrix_[i][j] += matrix_[i][n] * other.matrix_[n][j];
      }
    }
  }

  return res;
}

S21Matrix S21Matrix::operator*(double num) noexcept {
  S21Matrix res(rows_, cols_);
  for (int i{0}; i < rows_; i++) {
    for (int j{0}; j < cols_; j++) {
      res.matrix_[i][j] += matrix_[i][j] * num;
    }
  }

  return res;
}

bool S21Matrix::operator==(const S21Matrix &other) { return EqMatrix(other); }

S21Matrix &S21Matrix::operator+=(const S21Matrix &other) {
  SumMatrix(other);
  return *this;
}

S21Matrix &S21Matrix::operator-=(const S21Matrix &other) {
  SubMatrix(other);
  return *this;
}

S21Matrix &S21Matrix::operator*=(const S21Matrix &other) {
  MulMatrix(other);
  return *this;
}

S21Matrix &S21Matrix::operator*=(double num) noexcept {
  MulNumber(num);
  return *this;
}

double S21Matrix::operator()(int i, int j) { return matrix_.at(i).at(j); }
#include <vector>

#include "s21_matrix_oop.h"

S21Matrix::S21Matrix() noexcept {
  rows_ = 0;
  cols_ = 0;
}

S21Matrix::S21Matrix(int rows, int cols) {
  if (rows < 0 || cols < 0)
    throw std::invalid_argument("Некорректные параметры ( < 0 )");

  matrix_.resize(rows);
  for (int i{0}; i < rows; ++i) {
    matrix_[i].resize(cols);
  }

  rows_ = rows;
  cols_ = cols;
}

S21Matrix::S21Matrix(const S21Matrix &other) noexcept {
  rows_ = other.rows_;
  cols_ = other.cols_;

  matrix_.resize(rows_);
  for (int i{0}; i < rows_; ++i) {
    matrix_[i].resize(cols_);
    std::copy(other.matrix_[i].begin(), other.matrix_[i].end(),
              matrix_[i].begin());
  }
}

S21Matrix::S21Matrix(S21Matrix &&other) noexcept
    : rows_(other.rows_),
      cols_(other.cols_),
      matrix_(std::move(other.matrix_)) {
  other.rows_ = 0;
  other.cols_ = 0;
}

S21Matrix::~S21Matrix() noexcept {
  matrix_.clear();
  rows_ = 0;
  cols_ = 0;
}
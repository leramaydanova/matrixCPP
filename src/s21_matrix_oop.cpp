#include "s21_matrix_oop.h"

int S21Matrix::getRows() noexcept { return rows_; }

int S21Matrix::getCols() noexcept { return cols_; }

int &S21Matrix::editRows() noexcept { return rows_; }

int &S21Matrix::editCols() noexcept { return cols_; }

S21Matrix::matrix S21Matrix::getMatrix() noexcept { return matrix_; }

double &S21Matrix::editElem(int i, int j) { return matrix_.at(i).at(j); }

bool S21Matrix::EqMatrix(const S21Matrix &other) noexcept {
  if (rows_ != other.rows_ || cols_ != other.cols_) return false;

  for (int i{}; i < rows_; ++i) {
    for (int j{}; j < cols_; ++j) {
      if (matrix_[i][j] - other.matrix_[i][j] > 1e-7) return false;
    }
  }

  return true;
}

void S21Matrix::SumMatrix(const S21Matrix &other) {
  if (rows_ != other.rows_ || cols_ != other.cols_)
    throw std::invalid_argument("Разная размерность матриц");

  for (int i{0}; i < rows_; ++i) {
    for (int j{0}; j < cols_; ++j) {
      matrix_[i][j] += other.matrix_[i][j];
    }
  }
}

void S21Matrix::SubMatrix(const S21Matrix &other) {
  if (rows_ != other.rows_ || cols_ != other.cols_)
    throw std::invalid_argument("Разная размерность матриц");

  for (int i{0}; i < rows_; ++i) {
    for (int j{0}; j < cols_; ++j) {
      matrix_[i][j] -= other.matrix_[i][j];
    }
  }
}

void S21Matrix::MulNumber(const double num) noexcept {
  for (int i{0}; i < rows_; ++i) {
    for (int j{0}; j < cols_; ++j) {
      matrix_[i][j] *= num;
    }
  }
}

void S21Matrix::MulMatrix(const S21Matrix &other) {
  if (cols_ != other.rows_)
    throw std::invalid_argument(
        "Кол-во столбцов 1 матрицы не равно кол-ву строк 2 матрицы");

  S21Matrix res(rows_, other.cols_);
  for (int i{0}; i < rows_; i++) {
    for (int j{0}; j < other.cols_; j++) {
      for (int n{0}; n < cols_; n++) {
        res.editElem(i, j) += (*this)(i, n) * other.matrix_[n][j];
      }
    }
  }

  *this = std::move(res);
}

S21Matrix S21Matrix::Transpose() {
  S21Matrix res(cols_, rows_);
  for (int i{}; i < rows_; ++i) {
    for (int j{}; j < cols_; ++j) {
      res.editElem(j, i) = (*this)(i, j);
    }
  }

  return res;
}

S21Matrix S21Matrix::CalcComplements() {
  if (rows_ != cols_) {
    throw std::invalid_argument("Матрица должна быть квадратной");
  }

  if (cols_ <= 1) {
    return *this;
  }

  S21Matrix res(rows_, cols_);
  for (int i{}; i < rows_; ++i) {
    for (int j{}; j < cols_; ++j) {
      S21Matrix minor = GetMinorMatrix(i, j);
      double minor_det = minor.Determinant();
      res.editElem(i, j) = minor_det * ((i + j) % 2 == 0 ? 1 : -1);
    }
  }
  return res;
}

S21Matrix S21Matrix::GetMinorMatrix(int row, int col) {
  S21Matrix minor(rows_ - 1, cols_ - 1);
  int minor_row{};
  for (int i{}; i < rows_; ++i) {
    if (i != row) {
      int minor_col{};
      for (int j{}; j < cols_; ++j) {
        if (j != col) {
          minor.editElem(minor_row, minor_col) = (*this)(i, j);
          minor_col++;
        }
      }
      minor_row++;
    }
  }

  return minor;
}

double S21Matrix::Determinant() {
  if (rows_ != cols_) {
    throw std::invalid_argument("Матрица должна быть квадратной");
  }

  if (rows_ == 1) {
    return (*this)(0, 0);
  }

  if (rows_ == 2) {
    return (*this)(0, 0) * (*this)(1, 1) - (*this)(0, 1) * (*this)(1, 0);
  }

  double res{};
  for (int j{}; j < cols_; ++j) {
    S21Matrix minor = GetMinorMatrix(0, j);
    double minor_det = minor.Determinant();
    res += (*this)(0, j) * minor_det * ((j % 2 == 0) ? 1 : -1);
  }

  return res;
}

S21Matrix S21Matrix::InverseMatrix() {
  double det = Determinant();
  if (!det) {
    throw std::logic_error("Определитель равен 0");
  }

  if (cols_ == 1) {
    S21Matrix res(1, 1);
    res.editElem(0, 0) = 1 / (*this)(0, 0);
    return res;
  }

  S21Matrix minors = CalcComplements();
  S21Matrix res = minors.Transpose();
  res.MulNumber(1 / det);

  return res;
}
#ifndef MATRIX_H
#define MATRIX_H

#pragma once

#include <cstdint>
#include <vector>

struct MatrixOutOfRange {};

template <class ValueType, size_t N, size_t M>
struct Matrix {
  ValueType matrix_[N][M];

  size_t RowsNumber() const { return N; }

  size_t ColumnsNumber() const { return M; }

  ValueType& At(size_t a, size_t b) {
    if (a >= N || b >= M) {
      throw MatrixOutOfRange();
    }
    return matrix_[a][b];
  }

  const ValueType& At(size_t a, size_t b) const {
    if (a >= N || b >= M) {
      throw MatrixOutOfRange();
    }
    return matrix_[a][b];
  }

  ValueType& operator()(size_t a, size_t b) { return matrix_[a][b]; }

  const ValueType& operator()(size_t a, size_t b) const {
    return matrix_[a][b];
  }

  Matrix<ValueType, N, M> operator+(
      const Matrix<ValueType, N, M>& other) const {
    Matrix<ValueType, N, M> result;
    for (size_t i = 0; i < N; ++i) {
      for (size_t j = 0; j < M; ++j) {
        result.matrix_[i][j] = matrix_[i][j] + other.matrix_[i][j];
      }
    }
    return result;
  }

  Matrix<ValueType, N, M> operator-(
      const Matrix<ValueType, N, M>& other) const {
    Matrix<ValueType, N, M> result;
    for (size_t i = 0; i < N; ++i) {
      for (size_t j = 0; j < M; ++j) {
        result.matrix_[i][j] = matrix_[i][j] - other.matrix_[i][j];
      }
    }
    return result;
  }

  template <size_t K>
  Matrix<ValueType, N, K> operator*(
      const Matrix<ValueType, M, K>& other) const {
    Matrix<ValueType, N, K> result;
    for (size_t i = 0; i < N; ++i) {
      for (size_t j = 0; j < M; ++j) {
        for (size_t k = 0; k < K; ++k) {
          result.matrix_[i][k] += matrix_[i][j] * other.matrix_[j][k];
        }
      }
    }
    return result;
  }

  Matrix<ValueType, N, M> operator*(ValueType value) const {
    Matrix<ValueType, N, M> result;
    for (size_t i = 0; i < N; ++i) {
      for (size_t j = 0; j < M; ++j) {
        result.matrix_[i][j] = matrix_[i][j] * value;
      }
    }
    return result;
  }

  Matrix operator/(ValueType value) const {
    Matrix<ValueType, N, M> result;
    for (size_t i = 0; i < N; ++i) {
      for (size_t j = 0; j < M; ++j) {
        result.matrix_[i][j] = matrix_[i][j] / value;
      }
    }
    return result;
  }

  Matrix<ValueType, N, M>& operator+=(const Matrix<ValueType, N, M>& other) {
    *this = *this + other;
    return *this;
  }

  Matrix<ValueType, N, M>& operator-=(const Matrix<ValueType, N, M>& other) {
    *this = *this - other;
    return *this;
  }

  template <size_t K>
  Matrix<ValueType, N, K>& operator*=(const Matrix<ValueType, M, K>& other) {
    *this = *this * other;
    return *this;
  }

  Matrix<ValueType, N, M>& operator*=(const ValueType& value) {
    *this = *this * value;
    return *this;
  }

  Matrix<ValueType, N, M>& operator/=(const ValueType& value) {
    *this = *this / value;
    return *this;
  }

  bool operator==(const Matrix<ValueType, N, M>& other) const {
    for (size_t i = 0; i < N; ++i) {
      for (size_t j = 0; j < M; ++j) {
        if (matrix_[i][j] != other.matrix_[i][j]) {
          return false;
        }
      }
    }
    return true;
  }

  bool operator!=(const Matrix<ValueType, N, M>& other) const {
    return !(*this == other);
  }
};

template <class ValueType, size_t N, size_t M>
Matrix<ValueType, M, N> GetTransposed(const Matrix<ValueType, N, M>& matrix) {
  Matrix<ValueType, M, N> result;
  for (size_t i = 0; i < N; ++i) {
    for (size_t j = 0; j < M; ++j) {
      result(j, i) = matrix(i, j);
    }
  }
  return result;
}

template <class ValueType, size_t N, size_t M>
Matrix<ValueType, N, M> operator*(const Matrix<ValueType, N, M>& matrix,
                                  const ValueType& value) {
  Matrix<ValueType, N, M> result;
  for (size_t i = 0; i < N; ++i) {
    for (size_t j = 0; j < M; ++j) {
      result(i, j) = matrix(i, j) * value;
    }
  }
  return result;
}

template <class ValueType, size_t N, size_t M>
Matrix<ValueType, N, M> operator*(const ValueType& value,
                                  const Matrix<ValueType, N, M>& matrix) {
  return matrix * value;
}

template <class ValueType, size_t N, size_t M>
Matrix<ValueType, N, M> operator/(const Matrix<ValueType, N, M>& matrix,
                                  const ValueType& value) {
  Matrix<ValueType, N, M> result;
  for (size_t i = 0; i < N; ++i) {
    for (size_t j = 0; j < M; ++j) {
      result(i, j) = matrix(i, j) / value;
    }
  }
  return result;
}

template <class ValueType, size_t N, size_t M>
std::ostream& operator<<(std::ostream& ostream,
                         Matrix<ValueType, N, M> matrix) {
  for (size_t i = 0; i < N; ++i) {
    for (size_t j = 0; j < M; ++j) {
      ostream << matrix(i, j);
      if (j != M - 1) {
        ostream << ' ';
      }
    }
    if (i != M - 1) {
      ostream << '\n';
    }
  }

  return ostream;
}

template <class ValueType, size_t N, size_t M>
std::istream& operator>>(std::istream& istream,
                         Matrix<ValueType, N, M>& matrix) {
  for (size_t i = 0; i < N; ++i) {
    for (size_t j = 0; j < M; ++j) {
      istream >> matrix(i, j);
    }
  }

  return istream;
}

#endif

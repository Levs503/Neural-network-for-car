// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"

/**
 *
 */

namespace matrix {
template <class T> class MYPROJECT1_API MyMatrix {
public:
  MyMatrix(size_t row_, size_t col_);

  MyMatrix();

  ~MyMatrix();

  MyMatrix(const MyMatrix &rhs);

  T *operator[](const size_t index);

  MyMatrix &operator=(const MyMatrix &copy);

  MyMatrix operator+(const MyMatrix &plus);

  MyMatrix operator-(const MyMatrix &plus);

  T Rows();

  T Cols();

  MyMatrix<T> operator&(MyMatrix<T> &lhs);

  void RandFromTo(int from, int to);

  MyMatrix operator*(const MyMatrix &rhs2);
  void Print();
  MyMatrix Inverse();

  friend MyMatrix operator-(float g, MyMatrix<T> &mat) {
    matrix::MyMatrix<T> ret(mat);
    for (size_t f = 0; f < mat.Rows(); f++) {
      for (size_t a = 0; a < mat.Cols(); a++) {
        ret[f][a] = g - ret[f][a];
      }
    }
    return ret;
  }

  MyMatrix operator*(float coeff);

  friend bool operator==(const MyMatrix &fir, const MyMatrix &sec) {
    if (fir.row_ != sec.row_ || fir.col_ != sec.col_)
      return false;
    for (size_t i = 0; i < fir.row_; i++) {
      for (size_t j = 0; j < fir.row_; j++) {
        if (fir.values_[i][j] != sec.values_[i][j])
          return false;
      }
    }
    return true;
  }

  friend bool operator!=(const MyMatrix &fir, const MyMatrix &sec) {
    if (fir == sec)
      return false;
    return true;
  }

  void Transposition();

private:
  T **values_;
  size_t row_;
  size_t col_;
  void del();
  void Replace(size_t f, size_t s);
  void Addition(size_t wh, size_t from, float coef);
};

} // namespace matrix

template <class T>
matrix::MyMatrix<T> operator&(matrix::MyMatrix<T> &lhs,
                              matrix::MyMatrix<T> &&rhs) {
  return lhs & rhs;
}

template <class T>
matrix::MyMatrix<T>::MyMatrix(const size_t row_, const size_t col_)
    : col_(col_), row_(row_) {

  values_ = new T *[row_];
  for (size_t i = 0; i < row_; i++) {
    values_[i] = new T[col_];
    for (size_t j = 0; j < col_; j++) {
      values_[i][j] = 0;
    }
  }
}
template <class T> matrix::MyMatrix<T>::MyMatrix() : row_(0), col_(0) {
  values_ = nullptr;
}
template <class T> matrix::MyMatrix<T>::~MyMatrix() {
  if (values_ != nullptr)
    this->del();
}

template <class T>
matrix::MyMatrix<T>::MyMatrix(const MyMatrix &rhs)
    : MyMatrix(rhs.row_, rhs.col_) {
  for (size_t i = 0; i < row_; i++) {
    std::copy(rhs.values_[i], rhs.values_[i] + col_, values_[i]);
  }
}
template <class T>

T *matrix::MyMatrix<T>::operator[](const size_t index) {
  return values_[index];
}
template <class T>
matrix::MyMatrix<T> &matrix::MyMatrix<T>::operator=(const MyMatrix &copy) {
  if (&copy == this) {
    return *this;
  }
  this->del();
  row_ = copy.row_;
  col_ = copy.col_;
  if (row_ != 0 && col_ != 0) {
    values_ = new T *[row_];
    for (size_t i = 0; i < row_; i++) {
      values_[i] = new T[col_];
      std::copy(copy.values_[i], copy.values_[i] + col_, values_[i]);
    }
  }
  return *this;
}
template <class T>

matrix::MyMatrix<T> matrix::MyMatrix<T>::operator+(const MyMatrix &plus) {
  if (row_ != plus.row_ || col_ != plus.col_) {
    MyMatrix<T> retu(0, 0);
    return retu;
  }
  matrix::MyMatrix<T> retu(row_, col_);
  for (size_t i = 0; i < row_; i++) {
    for (size_t j = 0; j < col_; j++) {
      retu.values_[i][j] = values_[i][j] + plus.values_[i][j];
    }
  }
  return retu;
}
template <class T>

matrix::MyMatrix<T> matrix::MyMatrix<T>::operator-(const MyMatrix &plus) {
  if (row_ != plus.row_ || col_ != plus.col_) {
    MyMatrix<T> retu(0, 0);
    return retu;
  }
  matrix::MyMatrix<T> retu(row_, col_);
  for (size_t i = 0; i < row_; i++) {
    for (size_t j = 0; j < col_; j++) {
      retu.values_[i][j] = values_[i][j] - plus.values_[i][j];
    }
  }
  return retu;
}
template <class T>

T matrix::MyMatrix<T>::Rows() {
  return row_;
}
template <class T>

T matrix::MyMatrix<T>::Cols() {
  return col_;
}
template <class T>

matrix::MyMatrix<T> matrix::MyMatrix<T>::operator*(const MyMatrix &rhs2) {
  if (col_ != rhs2.row_) {
    matrix::MyMatrix<T> retu(0, 0);
    return retu;
  }
  matrix::MyMatrix<T> petr(row_, rhs2.col_);
  for (size_t i = 0; i < row_; i++) {
    for (size_t j = 0; j < rhs2.col_; j++) {
      for (size_t k = 0; k < col_; k++) {
        petr[i][j] += values_[i][k] * rhs2.values_[k][j];
      }
      // petr[i][j] = static_cast<int>((petr[i][j] + 0.00000001) * 1000) / 1000;
    }
  }
  return petr;
}
template <class T>

void matrix::MyMatrix<T>::Print() {
  for (size_t i = 0; i < row_; i++) {
    std::cout << std::endl << std::endl;
    for (size_t j = 0; j < col_; j++) {
      std::cout << values_[i][j] << " ";
    }
  }
}
template <class T>

matrix::MyMatrix<T> matrix::MyMatrix<T>::Inverse() {
  if (row_ != col_) {
    matrix::MyMatrix<T> retu(0, 0);
    return retu;
  }
  matrix::MyMatrix<float> big(row_, 2 * col_);
  for (size_t i = 0; i < row_; i++) {
    for (size_t j = 0; j < col_; j++) {
      big[i][j] = values_[i][j];
    }
    for (size_t j = col_; j < 2 * col_; j++) {
      big[i][j] = 0;
    }
    big[i][i + col_] = 1;
  }
  for (size_t i = 0; i < row_; i++) {
    size_t k = i;
    if (big[i][i] == 0) {
      while (big[k][i] == 0) {
        k++;
        if (k == row_) {
          matrix::MyMatrix<T> retu(0, 0); //������� ������
          return retu;
        }
      }
    }
    big.Replace(i, k);
    if (big[i][i] != 1 && big[i][i] != 0) {
      float a = big[i][i];
      for (size_t j = 0; j < 2 * col_; j++) {
        big[i][j] = big[i][j] / a;
      }
    }
    for (size_t j = 0; j < row_; j++) {
      if (i == j)
        continue;
      big.Addition(i, j, -(static_cast<float>(big[j][i])));
    }
  }
  matrix::MyMatrix<T> retu(row_, col_);
  for (size_t j = 0; j < col_; j++) {
    std::copy(big.values_[j] + col_, big.values_[j] + 2 * col_,
              retu.values_[j]);
  }
  return retu;
}

template <class T> void matrix::MyMatrix<T>::Transposition() {
  matrix::MyMatrix<T> new_mat(col_, row_);
  for (size_t r = 0; r < col_; r++) {
    for (size_t f = 0; f < row_; f++) {
      new_mat[r][f] = (*this)[f][r];
    }
  }
  *this = new_mat;
}
template <class T> void matrix::MyMatrix<T>::del() {
  for (size_t i = 0; i < row_; i++) {
    delete[] values_[i];
  }
  delete[] values_;
}

template <class T> void matrix::MyMatrix<T>::Replace(size_t f, size_t s) {
  T *arr = new T[col_];
  std::copy(values_[f], values_[f] + col_, arr);
  std::copy(values_[s], values_[s] + col_, values_[f]);
  std::copy(arr, arr + col_, values_[s]);
  delete[] arr;
}

template <class T>
void matrix::MyMatrix<T>::Addition(size_t wh, size_t from, float coef) {
  T *arr = new T[col_];
  std::copy(values_[wh], values_[wh] + col_, arr);
  for (size_t i = 0; i < col_; i++) {
    arr[i] *= coef;
    values_[from][i] += arr[i];
  }
  delete[] arr;
}

template <class T> void matrix::MyMatrix<T>::RandFromTo(int from, int to) {
  int interval = (to - from) * 10000;
  for (size_t g = 0; g < row_; g++) {
    for (size_t f = 0; f < col_; f++) {
      (*this)[g][f] = (T(rand() % (interval)) / 10000) + from;
    }
  }
}

template <class T>
matrix::MyMatrix<T> matrix::MyMatrix<T>::operator*(float coeff) {
  matrix::MyMatrix<float> ret(*this);
  for (size_t f = 0; f < row_; f++) {
    for (size_t a = 0; a < col_; a++) {
      ret[f][a] *= coeff;
    }
  }
  return ret;
}

template <class T>
matrix::MyMatrix<T> matrix::MyMatrix<T>::operator&(matrix::MyMatrix<T> &lhs) {
  matrix::MyMatrix<T> ret(lhs.Rows(), lhs.Cols());
  for (size_t g = 0; g < lhs.row_; g++) {
    for (size_t k = 0; k < lhs.col_; k++) {
      ret[g][k] = lhs[g][k] * (*this)[g][k];
    }
  }
  return ret;
}

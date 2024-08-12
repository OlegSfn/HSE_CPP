#ifndef ARRAY__ARRAY_H_
#define ARRAY__ARRAY_H_
#define ARRAY_TRAITS_IMPLEMENTED

#include <algorithm>
#include <iostream>
#include <stdexcept>

class ArrayOutOfRange : public std::out_of_range {
 public:
  ArrayOutOfRange() : std::out_of_range("ArrayOutOfRange") {
  }
};

template <typename T, size_t N>
class Array {
 public:
  T array[N];

  T& operator[](size_t idx) {
    return array[idx];
  }

  const T& operator[](size_t idx) const {
    return array[idx];
  }

  T& At(size_t idx) {
    if (idx >= N) {
      throw ArrayOutOfRange{};
    }
    return array[idx];
  }

  const T& At(size_t idx) const {
    if (idx >= N) {
      throw ArrayOutOfRange{};
    }
    return array[idx];
  }

  T& Front() {
    return array[0];
  }

  const T& Front() const {
    return array[0];
  }

  T& Back() {
    return array[N - 1];
  }

  const T& Back() const {
    return array[N - 1];
  }

  T* Data() {
    return array;
  }

  const T* Data() const {
    return array;
  }

  [[nodiscard]] size_t Size() const {
    return N;
  }

  [[nodiscard]] bool Empty() const {
    return N == 0;
  }

  void Fill(const T& value) {
    for (size_t i = 0; i < N; ++i) {
      array[i] = value;
    }
  }

  void Swap(Array<T, N>& other) {
    for (size_t i = 0; i < N; ++i) {
      std::swap(array[i], other[i]);
    }
  }
};

template <typ ename T>
constexpr size_t GetSize(T) {
  return 0;
}

template <typename T, size_t N>
constexpr size_t GetSize(T (&)[N]) {
  return N;
}

template <typename T>
constexpr size_t GetRank(T) {
  return 0;
}

template <typename T, size_t N>
constexpr size_t GetRank(T (&array)[N]) {
  return 1 + GetRank(array[0]);
}

template <typename T>
constexpr size_t GetNumElements(T) {
  return 1;
}

template <typename T, size_t N>
constexpr size_t GetNumElements(T (&array)[N]) {
  return N * GetNumElements(array[0]);
}

#endif  // ARRAY__ARRAY_H_

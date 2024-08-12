#ifndef VECTOR__VECTOR_H_
#define VECTOR__VECTOR_H_

#include <algorithm>
#include <iostream>
#include <stdexcept>

template <typename T>
class Vector {
 private:
  size_t size_;
  size_t capacity_;
  T* data_;

 public:
  using ValueType = T;
  using Pointer = T*;
  using ConstPointer = const T*;
  using Reference = T&;
  using ConstReference = const T&;
  using SizeType = std::size_t;
  using Iterator = T*;
  using ConstIterator = const T*;
  using ReverseIterator = std::reverse_iterator<Iterator>;
  using ConstReverseIterator = std::reverse_iterator<ConstIterator>;

  Vector() : size_(0), capacity_(0), data_(nullptr) {
  }

  explicit Vector(SizeType size) : size_(size), capacity_(size), data_(nullptr) {
    if (size_ > 0) {
      try {
        data_ = new ValueType[size_];
      } catch (...) {
        size_ = 0;
        capacity_ = 0;
        throw;
      }
    }
  }
  Vector(SizeType size, const T& value) : size_(size), capacity_(size), data_(nullptr) {
    if (size_ > 0) {
      try {
        data_ = new ValueType[size_];
        std::fill(data_, data_ + size, value);
      } catch (...) {
        delete[] data_;
        data_ = nullptr;
        size_ = 0;
        capacity_ = 0;
        throw;
      }
    }
  }

  template <class Iterator, class = std::enable_if_t<std::is_base_of_v<
                                std::forward_iterator_tag, typename std::iterator_traits<Iterator>::iterator_category>>>
  Vector(Iterator first, Iterator last) : size_(last - first), capacity_(last - first), data_(nullptr) {
    if (last - first != 0) {
      try {
        data_ = new ValueType[last - first];
        std::copy(first, last, data_);
      } catch (...) {
        delete[] data_;
        data_ = nullptr;
        size_ = 0;
        capacity_ = 0;
        throw;
      }
    }
  }

  Vector(std::initializer_list<T> list) : size_(list.size()), capacity_(list.size()), data_(nullptr) {
    if (size_ != 0) {
      try {
        data_ = new ValueType[size_];
        std::copy(list.begin(), list.end(), data_);
      } catch (...) {
        delete[] data_;
        data_ = nullptr;
        size_ = 0;
        capacity_ = 0;
        throw;
      }
    }
  }

  Vector(const Vector& other) : size_(other.size_), capacity_(other.capacity_), data_(nullptr) {
    if (size_ != 0) {
      try {
        data_ = new ValueType[size_];
        std::copy(other.begin(), other.end(), data_);
      } catch (...) {
        delete[] data_;
        data_ = nullptr;
        size_ = 0;
        capacity_ = 0;
        throw;
      }
    }
  }

  Vector(Vector&& other) noexcept : size_(other.size_), capacity_(other.capacity_), data_(nullptr) {
    if (size_ > 0) {
      Swap(other);
      other.size_ = 0;
      other.capacity_ = 0;
    }
  }

  Vector& operator=(const Vector& other) {
    if (this != &other) {
      delete[] data_;
      size_ = other.size_;
      capacity_ = other.capacity_;
      data_ = nullptr;
      if (size_ > 0) {
        data_ = new ValueType[size_];
        std::copy(other.begin(), other.end(), data_);
      }
    }

    return *this;
  }

  Vector& operator=(Vector&& other) noexcept {
    if (this != &other) {
      delete[] data_;
      Swap(other);
      other.data_ = nullptr;
      other.size_ = 0;
      other.capacity_ = 0;
    }

    return *this;
  }

  ~Vector() {
    delete[] data_;
  }

  [[nodiscard]] SizeType Size() const {
    return size_;
  }

  [[nodiscard]] SizeType Capacity() const {
    return capacity_;
  }

  [[nodiscard]] bool Empty() const {
    return size_ == 0;
  }

  Reference operator[](SizeType index) {
    return data_[index];
  }

  ConstReference operator[](SizeType index) const {
    return data_[index];
  }

  Reference At(SizeType index) {
    if (index >= size_) {
      throw std::out_of_range("index was out of range");
    }
    return data_[index];
  }

  ConstReference At(SizeType index) const {
    if (index >= size_) {
      throw std::out_of_range("index was out of range");
    }

    return data_[index];
  }

  Reference Front() {
    return data_[0];
  }

  ConstReference Front() const {
    return data_[0];
  };

  Reference Back() {
    return data_[size_ - 1];
  }

  ConstReference Back() const {
    return data_[size_ - 1];
  };

  Pointer Data() {
    return data_;
  }

  ConstPointer Data() const {
    return data_;
  }

  void Swap(Vector& other) {
    std::swap(data_, other.data_);
    std::swap(size_, other.size_);
    std::swap(capacity_, other.capacity_);
  }

  void Resize(SizeType new_size) {
    if (new_size == size_) {
      return;
    }

    if (new_size == 0) {
      size_ = 0;
      data_ = nullptr;
      return;
    }

    if (new_size > capacity_) {
      Reserve(new_size);
    }
    size_ = new_size;
  }

  void Resize(SizeType new_size, const ValueType& value) {
    Pointer last_data = data_;
    SizeType last_capacity = capacity_;
    if (new_size > size_) {
      try {
        if (new_size > capacity_) {
          data_ = new ValueType[new_size];
          if (size_ > 0) {
            std::copy(std::make_move_iterator(last_data), std::make_move_iterator(last_data + size_), data_);
          }
        }

        std::fill(data_ + size_, data_ + new_size, value);
        if (new_size > capacity_) {
          capacity_ = new_size;
        }
      } catch (...) {
        if (new_size > capacity_) {
          delete[] data_;
        }
        data_ = last_data;
        throw;
      }
    }

    if (new_size > last_capacity) {
      delete[] last_data;
    }
    size_ = new_size;
  }

  void Reserve(SizeType new_cap) {
    if (new_cap <= capacity_) {
      return;
    }

    Pointer last_data = data_;
    try {
      data_ = new ValueType[new_cap];
    } catch (...) {
      throw;
    }

    try {
      if (size_ > 0) {
        std::copy(std::make_move_iterator(last_data), std::make_move_iterator(last_data + size_), data_);
      }
      capacity_ = new_cap;
    } catch (...) {
      delete[] data_;
      data_ = last_data;
      throw;
    }

    delete[] last_data;
  }

  void ShrinkToFit() {
    if (capacity_ == size_) {
      return;
    }
    if (size_ == 0) {
      delete[] data_;
      data_ = nullptr;
      capacity_ = 0;
      return;
    }

    Pointer last_data = data_;
    try {
      data_ = new ValueType[size_];
    } catch (...) {
      throw;
    }

    try {
      std::copy(std::make_move_iterator(last_data), std::make_move_iterator(last_data + size_), data_);
      capacity_ = size_;
    } catch (...) {
      delete[] data_;
      data_ = last_data;
      throw;
    }

    delete[] last_data;
  }

  void Clear() {
    size_ = 0;
  }

  void PushBack(const ValueType& value) {
    if (capacity_ == 0) {
      try {
        data_ = new ValueType[1];
        data_[0] = std::move(value);
        size_ = 1;
        capacity_ = 1;
      } catch (...) {
        delete[] data_;
        data_ = nullptr;
        size_ = 0;
        capacity_ = 0;
        throw;
      }
      return;
    }

    Pointer last_data = data_;
    SizeType last_size = size_;
    SizeType last_capacity = capacity_;
    try {
      if (size_ == capacity_) {
        data_ = new ValueType[2 * capacity_];
      }
    } catch (...) {
      throw;
    }

    try {
      if (size_ == capacity_ && size_ > 0) {
        std::copy(std::make_move_iterator(last_data), std::make_move_iterator(last_data + size_), data_);
      }
      data_[size_] = std::move(value);
      if (size_ == capacity_) {
        capacity_ *= 2;
      }
      ++size_;
    } catch (...) {
      if (size_ == capacity_) {
        delete[] data_;
        data_ = last_data;
      }
      throw;
    }

    if (last_size == last_capacity) {
      delete[] last_data;
    }
  }

  void PushBack(ValueType&& value) {
    if (capacity_ == 0) {
      try {
        data_ = new ValueType[1];
        data_[0] = std::move(value);
        size_ = 1;
        capacity_ = 1;
      } catch (...) {
        delete[] data_;
        data_ = nullptr;
        size_ = 0;
        capacity_ = 0;
        throw;
      }
      return;
    }

    Pointer last_data = data_;
    SizeType last_size = size_;
    SizeType last_capacity = capacity_;
    try {
      if (size_ == capacity_) {
        data_ = new ValueType[2 * capacity_];
      }
    } catch (...) {
      throw;
    }

    try {
      if (size_ == capacity_ && size_ > 0) {
        std::copy(std::make_move_iterator(last_data), std::make_move_iterator(last_data + size_), data_);
      }
      data_[size_] = std::move(value);
      if (size_ == capacity_) {
        capacity_ *= 2;
      }
      ++size_;
    } catch (...) {
      if (size_ == capacity_) {
        delete[] data_;
        data_ = last_data;
      }
      throw;
    }

    if (last_size == last_capacity) {
      delete[] last_data;
    }
  }

  void PopBack() {
    --size_;
  }

  bool operator<(const Vector& other) const {
    return std::lexicographical_compare(data_, data_ + size_, other.data_, other.data_ + other.size_);
  }
  bool operator>(const Vector& other) const {
    return other < *this;
  }

  bool operator==(const Vector& other) const {
    if (size_ != other.size_) {
      return false;
    }
    return std::equal(data_, data_ + size_, other.data_);
  }

  bool operator!=(const Vector& other) const {
    return !(*this == other);
  }

  bool operator<=(const Vector& other) const {
    return !(*this > other);
  }
  bool operator>=(const Vector& other) const {
    return !(*this < other);
  }

  Iterator begin() {  // NOLINT
    return data_;
  }

  ConstIterator begin() const {  // NOLINT
    return data_;
  }

  ConstIterator cbegin() const {  // NOLINT
    return data_;
  }

  Iterator end() {  // NOLINT
    return data_ + size_;
  }

  ConstIterator end() const {  // NOLINT
    return data_ + size_;
  }

  ConstIterator cend() const {  // NOLINT
    return data_ + size_;
  }

  ReverseIterator rbegin() {  // NOLINT
    return std::reverse_iterator<Pointer>(end());
  }

  ConstReverseIterator rbegin() const {  // NOLINT
    return std::reverse_iterator<ConstIterator>(end());
  }

  ConstReverseIterator crbegin() const {  // NOLINT
    return std::reverse_iterator<ConstIterator>(cend());
  }

  ReverseIterator rend() {  // NOLINT
    return std::reverse_iterator<Pointer>(begin());
  }

  ConstReverseIterator rend() const {  // NOLINT
    return std::reverse_iterator<ConstIterator>(begin());
  }

  ConstReverseIterator crend() const {  // NOLINT
    return std::reverse_iterator<ConstIterator>(cbegin());
  }
};

#endif  // VECTOR__VECTOR_H_

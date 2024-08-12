#ifndef SHAREDPTR__SHARED_PTR_H_
#define SHAREDPTR__SHARED_PTR_H_
#define WEAK_PTR_IMPLEMENTED

#include <algorithm>
#include <cstdio>

class BadWeakPtr {};

struct Counter {
  size_t strong_count = 0;
  size_t weak_count = 0;
};

template <typename T>
class WeakPtr;

template <typename T>
class SharedPtr {
  friend class WeakPtr<T>;

 private:
  T* pointer_;
  Counter* counter_;

 public:
  SharedPtr() : pointer_(nullptr), counter_(nullptr) {
  }

  SharedPtr(T* pointer) : pointer_(pointer), counter_(nullptr) {  // NOLINT
    if (pointer_ != nullptr) {
      counter_ = new Counter;
      ++counter_->strong_count;
    }
  }

  SharedPtr(const SharedPtr& other) : pointer_(other.pointer_), counter_(other.counter_) {
    if (counter_ != nullptr) {
      ++counter_->strong_count;
    }
  }

  SharedPtr(const WeakPtr<T>& other) : pointer_(other.pointer_), counter_(other.counter_) {  // NOLINT
    if (other.IsExpired()) {
      throw BadWeakPtr{};
    }

    if (counter_ != nullptr) {
      ++counter_->strong_count;
    }
  }

  SharedPtr(SharedPtr&& other) noexcept : pointer_(other.pointer_), counter_(other.counter_) {
    other.pointer_ = nullptr;
    other.counter_ = nullptr;
  }

  SharedPtr<T>& operator=(const SharedPtr& other) {
    if (this != &other) {
      if (counter_ != nullptr) {
        DetachFromResource();
      }

      pointer_ = other.pointer_;
      counter_ = other.counter_;

      if (counter_ != nullptr) {
        ++counter_->strong_count;
      }
    }
    return *this;
  }

  SharedPtr<T>& operator=(SharedPtr&& other) noexcept {
    if (this != &other) {
      if (counter_ != nullptr) {
        DetachFromResource();
      }

      pointer_ = other.pointer_;
      counter_ = other.counter_;
      other.pointer_ = nullptr;
      other.counter_ = nullptr;
    }
    return *this;
  }

  void Reset(T* ptr = nullptr) {
    DetachFromResource();
    pointer_ = ptr;
    if (counter_ != nullptr && counter_->strong_count == 0 && counter_->weak_count == 0) {
      delete counter_;
      counter_ = new Counter;
    } else {
      counter_ = new Counter;
    }

    if (pointer_ != nullptr) {
      ++counter_->strong_count;
    }
  }

  void Swap(SharedPtr& other) {
    std::swap(*this, other);
  }

  T* Get() const {
    return pointer_;
  }

  [[nodiscard]] size_t UseCount() const {
    if (counter_ == nullptr) {
      return 0;
    }
    return counter_->strong_count;
  }

  T& operator*() const {
    return *pointer_;
  }

  explicit operator bool() const {
    return pointer_ != nullptr;
  }

  T* operator->() const {
    return pointer_;
  }

  void DetachFromResource() {
    if (counter_ != nullptr && (counter_->strong_count == 0 || --counter_->strong_count == 0)) {
      delete pointer_;
      if (counter_->weak_count == 0) {
        delete counter_;
      }
      counter_ = nullptr;
    }

    pointer_ = nullptr;
  }

  ~SharedPtr() {
    if (counter_ != nullptr && (counter_->strong_count == 0 || --counter_->strong_count == 0)) {
      delete pointer_;
      if (counter_->weak_count == 0) {
        delete counter_;
      }
    }
  }
};

template <typename T>
class WeakPtr {
  friend class SharedPtr<T>;

 private:
  T* pointer_;
  Counter* counter_;

 public:
  WeakPtr() : pointer_(nullptr), counter_(nullptr) {
  }

  WeakPtr(T* pointer) : pointer_(pointer), counter_(nullptr) {  // NOLINT
    if (pointer_ != nullptr) {
      counter_ = new Counter;
      ++counter_->weak_count;
    }
  }

  WeakPtr(const WeakPtr& other) : pointer_(other.pointer_), counter_(other.counter_) {
    if (counter_ != nullptr) {
      ++counter_->weak_count;
    }
  }

  WeakPtr(const SharedPtr<T>& other) : pointer_(other.pointer_), counter_(other.counter_) {  // NOLINT
    if (counter_ != nullptr) {
      ++counter_->weak_count;
    }
  }

  WeakPtr(WeakPtr&& other) noexcept : pointer_(other.pointer_), counter_(other.counter_) {
    other.pointer_ = nullptr;
    other.counter_ = nullptr;
  }

  WeakPtr<T>& operator=(const WeakPtr& other) {
    if (this != &other) {
      if (counter_ != nullptr) {
        DetachFromResource();
      }

      pointer_ = other.pointer_;
      counter_ = other.counter_;

      if (counter_ != nullptr) {
        ++counter_->weak_count;
      }
    }
    return *this;
  }

  WeakPtr<T>& operator=(WeakPtr&& other) noexcept {
    if (this != &other) {
      if (counter_ != nullptr) {
        DetachFromResource();
      }

      pointer_ = other.pointer_;
      counter_ = other.counter_;
      other.pointer_ = nullptr;
      other.counter_ = nullptr;
    }
    return *this;
  }

  void Reset(T* ptr = nullptr) {
    DetachFromResource();
    pointer_ = ptr;
    if (counter_ != nullptr && counter_->strong_count == 0 && counter_->weak_count == 0) {
      delete counter_;
      counter_ = new Counter;
    } else {
      counter_ = new Counter;
    }

    if (pointer_ != nullptr) {
      ++counter_->weak_count;
    }
  }

  [[nodiscard]] size_t UseCount() const {
    if (counter_ == nullptr) {
      return 0;
    }
    return counter_->strong_count;
  }

  void DetachFromResource() {
    if (counter_ != nullptr) {
      if (counter_->weak_count != 0) {
        --counter_->weak_count;
      }

      if (counter_->strong_count == 0) {
        delete pointer_;
        if (counter_->weak_count == 0) {
          delete counter_;
        }
        counter_ = nullptr;
      }
    }

    pointer_ = nullptr;
  }

  [[nodiscard]] bool IsExpired() const {
    if (counter_ == nullptr) {
      return true;
    }

    return counter_->strong_count == 0;
  }

  SharedPtr<T> Lock() const {
    if (IsExpired()) {
      return SharedPtr<T>(nullptr);
    }

    return SharedPtr(*this);
  }

  ~WeakPtr() {
    if (counter_ != nullptr && (counter_->weak_count == 0 || --counter_->weak_count == 0) &&
        counter_->strong_count == 0) {
      delete counter_;
    }
  }
};

template <typename T, typename... Args>
SharedPtr<T> MakeShared(Args&&... args) {
  return SharedPtr<T>(new T(std::forward<Args>(args)...));
}

#endif  // SHAREDPTR__SHARED_PTR_H_

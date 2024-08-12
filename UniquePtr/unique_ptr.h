#ifndef TEST__UNIQUE_PTR_H_
#define TEST__UNIQUE_PTR_H_

template <class T>
class UniquePtr {
 private:
  T* pointer_;

 public:
  UniquePtr() : pointer_(nullptr) {};
  UniquePtr(T* pointer) : pointer_(pointer) {};  // NOLINT
  UniquePtr(const UniquePtr&) = delete;
  UniquePtr& operator=(const UniquePtr& other) = delete;

  UniquePtr(UniquePtr&& other) noexcept {
    pointer_ = other.pointer_;
    other.pointer_ = nullptr;
  }

  UniquePtr& operator=(UniquePtr&& other) noexcept {
    if (this != &other) {
      delete pointer_;
      pointer_ = other.pointer_;
      other.pointer_ = nullptr;
    }
    return *this;
  }

  T* Release() {
    T* return_value = pointer_;
    pointer_ = nullptr;
    return return_value;
  }

  void Reset(T* ptr = nullptr) {
    delete pointer_;
    pointer_ = ptr;
  }

  void Swap(UniquePtr& swap_ptr) {
    T* temp_ptr = swap_ptr.pointer_;
    swap_ptr.pointer_ = Get();
    pointer_ = temp_ptr;
  }

  T* Get() const {
    return pointer_;
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

  ~UniquePtr() {
    delete pointer_;
  }
};

#endif  // TEST__UNIQUE_PTR_H_
#ifndef UNORDEREDSET__UNORDERED_SET_H_
#define UNORDEREDSET__UNORDERED_SET_H_

#include <algorithm>
#include <vector>
#include <list>

template <typename KeyT>
class UnorderedSet {
 public:
  UnorderedSet() : size_(0) {
  }

  explicit UnorderedSet(size_t count) : size_(0) {
    data_.resize(count);
  }

  template <class Iterator, class = std::enable_if_t<std::is_base_of_v<
                                std::forward_iterator_tag, typename std::iterator_traits<Iterator>::iterator_category>>>
  UnorderedSet(Iterator first, Iterator last) : size_(0) {
    while (first != last) {
      Insert(*first);
      ++first;
    }
  }

  UnorderedSet(const UnorderedSet& other) : size_(other.size_) {
    data_ = other.data_;
  }

  UnorderedSet(UnorderedSet&& other) noexcept : data_(std::move(other.data_)), size_(other.size_) {
    other.size_ = 0;
  }

  UnorderedSet& operator=(const UnorderedSet& other) {
    data_ = other.data_;
    size_ = other.size_;

    return *this;
  }

  UnorderedSet& operator=(UnorderedSet&& other) noexcept {
    data_ = std::move(other.data_);
    size_ = other.size_;
    other.size_ = 0;

    return *this;
  }

  [[nodiscard]] size_t Size() const {
    return size_;
  }

  [[nodiscard]] bool Empty() const {
    return size_ == 0;
  }

  void Clear() {
    data_.clear();
    size_ = 0;
  }

  void Insert(const KeyT& item) {
    if (BucketCount() == 0) {
      data_.push_back({item});
    } else {
      if (LoadFactor() == 1) {
        Rehash(2 * data_.size());
      }
      data_[Bucket(item)].push_back(item);
    }

    ++size_;
  }

  void Insert(KeyT&& item) {
    Insert(item);
  }

  void Erase(const KeyT& item) {
    if (size_ == 0) {
      return;
    }

    size_t bucket_id = Bucket(item);
    const auto& it = std::find(data_[bucket_id].begin(), data_[bucket_id].end(), item);
    if (it != data_[bucket_id].end()) {
      data_[bucket_id].erase(it);
      --size_;
    }
  }

  bool Find(const KeyT& item) const {
    if (size_ == 0) {
      return false;
    }

    size_t bucket_id = Bucket(item);
    return std::find(data_[bucket_id].begin(), data_[bucket_id].end(), item) != data_[bucket_id].end();
  }

  void Rehash(size_t new_bucket_count) {
    if (new_bucket_count == BucketCount() || size_ / static_cast<double>(new_bucket_count) > 1) {
      return;
    }

    std::vector<std::list<KeyT>> new_data(new_bucket_count);
    for (auto& lst : data_) {
      while (!lst.empty()) {
        KeyT& item = lst.front();
        new_data[hasher_(item) % new_data.size()].push_back(std::move(item));
        lst.pop_front();
      }
    }

    data_ = std::move(new_data);
  }

  void Reserve(size_t new_bucket_count) {
    if (new_bucket_count <= BucketCount()) {
      return;
    }
    Rehash(new_bucket_count);
  }

  [[nodiscard]] size_t BucketCount() const {
    return data_.size();
  }

  [[nodiscard]] size_t BucketSize(size_t id) const {
    if (id >= data_.size()) {
      return 0;
    }
    return data_[id].size();
  }

  [[nodiscard]] size_t Bucket(const KeyT& key) const {
    return hasher_(key) % data_.size();
  }

  [[nodiscard]] double LoadFactor() const {
    if (data_.empty()) {
      return 0;
    }
    return static_cast<double>(size_) / data_.size();
  }

 private:
  std::vector<std::list<KeyT>> data_;
  std::hash<KeyT> hasher_;
  size_t size_;
};

#endif  // UNORDEREDSET__UNORDERED_SET_H_
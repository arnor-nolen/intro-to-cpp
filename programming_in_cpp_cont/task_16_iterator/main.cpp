#include <iostream>
#include <list>
#include <vector>

template <class T> class VectorList {
private:
  using VectT = std::vector<T>;
  using ListT = std::list<VectT>;
  using ListTIt = typename ListT::const_iterator;
  using VectTIt = typename VectT::const_iterator;

public:
  using value_type = T;

  VectorList() = default;
  VectorList(VectorList const &) = default;
  VectorList(VectorList &&) = default;

  VectorList &operator=(VectorList &&) = default;
  VectorList &operator=(VectorList const &) = default;

  template <class It> void append(It p, It q) {
    if (p != q)
      data_.push_back(VectT(p, q));
  }

  bool empty() const { return size() == 0; }

  size_t size() const {
    size_t size = 0;
    for (auto &i : data_) {
      size += i.size();
    }
    return size;
  }

  struct const_iterator
      : std::iterator<std::bidirectional_iterator_tag, const value_type> {
    const_iterator() = default;
    const_iterator(const const_iterator &other) = default;
    const_iterator(ListTIt &list_it, VectTIt &vector_it, ListT const *p)
        : list_it_(list_it), vector_it_(vector_it), p_(p) {}
    const_iterator &operator=(const const_iterator &) = default;
    ~const_iterator() = default;

    const_iterator &operator++() {
      if (++vector_it_ == list_it_->cend()) {
        if (++list_it_ == p_->cend())
          return *this;
        vector_it_ = list_it_->cbegin();
      }
      return *this;
    }
    const_iterator operator++(int) {
      auto temp = *this;
      ++*this;
      return temp;
    }

    const_iterator &operator--() {
      if (list_it_ == p_->cend())
        --list_it_;
      if (vector_it_ == list_it_->cbegin()) {
        if (list_it_ == p_->cbegin())
          return *this;
        --list_it_;
        vector_it_ = list_it_->cend();
      }
      --vector_it_;
      return *this;
    }
    const_iterator operator--(int) {
      auto temp = *this;
      --*this;
      return temp;
    }

    bool operator==(const const_iterator &other) const {
      return vector_it_ == other.vector_it_;
    }
    bool operator!=(const const_iterator &other) const {
      return !operator==(other);
    }

    const value_type &operator*() const { return *vector_it_; }
    const value_type *operator->() const { return &*vector_it_; };

  private:
    ListTIt list_it_;
    VectTIt vector_it_;
    ListT const *p_;
  };

  const_iterator begin() const {
    if (empty())
      return const_iterator();
    auto list_it = data_.cbegin();
    auto vector_it = data_.front().cbegin();
    return const_iterator(list_it, vector_it, &data_);
  }
  const_iterator end() const {
    if (empty())
      return const_iterator();
    auto list_it = data_.cend();
    auto vector_it = data_.back().cend();
    return const_iterator(list_it, vector_it, &data_);
  }

  using const_reverse_iterator = std::reverse_iterator<const_iterator>;

  const_reverse_iterator rbegin() const {
    return const_reverse_iterator(end());
  }
  const_reverse_iterator rend() const {
    return const_reverse_iterator(begin());
  }

private:
  ListT data_;
};

// Tests from the forum
int main() {
  VectorList<char> vlist;

  std::vector<char> v1 = {'A', 'B', 'C'};
  std::vector<char> v2 = {'D', 'E', 'F', 'G'};

  vlist.append(v1.begin(), v1.end());
  vlist.append(v2.begin(), v2.end());

  auto i = vlist.begin();

  std::cout << "Size is " << vlist.size() << std::endl;
  std::cout << "begin is " << *i << std::endl;
  std::cout << "std::distance(begin,end) "
            << std::distance(vlist.begin(), vlist.end()) << std::endl;
  std::cout << "*(++begin) == 'B'? " << (*++vlist.begin() == 'B') << std::endl;
  std::cout << "*(++begin) == 'A'? " << (*++vlist.begin() == 'A') << std::endl;
  std::cout << std::endl;

  std::cout << "Test ++i" << std::endl;
  for (i = vlist.begin(); i != vlist.end(); ++i)
    std::cout << *i << " ";
  std::cout << std::endl;
  std::cout << std::endl;

  std::cout << "Test i++" << std::endl;
  for (i = vlist.begin(); i != vlist.end(); i++)
    std::cout << *i << " ";
  std::cout << std::endl;
  std::cout << std::endl;

  std::cout << "Test --i" << std::endl;
  for (i = vlist.end(); i != vlist.begin();)
    std::cout << *--i << " ";
  std::cout << std::endl;
  std::cout << std::endl;

  std::cout << "Test i--" << std::endl;
  for (i = vlist.end(); i != vlist.begin();) {
    i--;
    std::cout << *i << " ";
  }
  std::cout << std::endl;
  std::cout << std::endl;

  auto j = vlist.rbegin();
  std::cout << "rbegin is " << *j << std::endl;
  j = --vlist.rend();
  std::cout << "rend is " << *j << std::endl;
  std::cout << std::endl;

  std::cout << "Test reverse_const_iterator ++" << std::endl;
  for (j = vlist.rbegin(); j != vlist.rend(); ++j)
    std::cout << *j << " ";
  std::cout << std::endl;

  return 0;
}
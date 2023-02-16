#ifndef ARRAY_HPP
#define ARRAY_HPP

#include <iostream>

template <typename T, int N>
class array {
  typedef T value_type;
  typedef value_type* pointer;
  typedef const value_type* const_pointer;
  typedef value_type& reference;
  typedef const value_type& const_reference;
  typedef value_type* iterator;
  typedef const value_type* const_iterator;
  typedef std::size_t size_type;
  typedef std::ptrdiff_t difference_type;
  typedef std::reverse_iterator<iterator> reverse_iterator;
  typedef std::reverse_iterator<const_iterator> const_reverse_iterator;

 public:
  array() = default;

  array(const array<value_type, N>& original) {
    fill(original);
  }

  array(std::initializer_list<value_type> l) {
    int i = 0;
    for (const auto& element : l) {
      m_buffer[i] = element;
      i++;
    }
  }

  constexpr reference at(int index) {
    // TODO: Bound check
    return m_buffer[index];
  }

  constexpr const_reference at(int index) const {
    return m_buffer[index];
  }

  void fill(const array<value_type, N>& other) {
    for (int i = 0; i < N; i++) m_buffer[i] = other.m_buffer[i];
  }

  // Iterators
  constexpr iterator begin() noexcept { return iterator(data()); };

  constexpr const_iterator begin() const noexcept { return const_iterator(data()); };

  constexpr iterator end() noexcept { return iterator(data() + N); }

  constexpr const_iterator end() const noexcept { return const_iterator(data() + N); }

  constexpr reverse_iterator rbegin() noexcept { return reverse_iterator(end()); }

  constexpr const_reverse_iterator rbegin() const noexcept { return const_reverse_iterator(end()); }

  constexpr reverse_iterator rend() noexcept { return reverse_iterator(begin()); }

  constexpr const_reverse_iterator rend() const noexcept { return const_reverse_iterator(begin()); }

  constexpr const_iterator cbegin() const noexcept { return const_iterator(data()); }

  constexpr const_iterator cend() const noexcept { return const_iterator(data() + N); }

  constexpr const_reverse_iterator crbegin() const noexcept { return const_reverse_iterator(end()); }

  constexpr const_reverse_iterator crend() const noexcept { return const_reverse_iterator(begin()); }

  [[nodiscard]] constexpr size_type size() const noexcept { return N; }
  [[nodiscard]] constexpr size_type max_size() const noexcept { return N; }

  [[nodiscard]] constexpr bool empty() const noexcept { return size() == 0; }

  constexpr reference operator[](size_type n) noexcept { return m_buffer[n]; }

  constexpr const_reference operator[](size_type n) const noexcept { return m_buffer[n]; }

  constexpr reference front() noexcept { return m_buffer[0]; }

  constexpr const_reference front() const noexcept { return m_buffer[0]; }

  constexpr reference back() noexcept { return m_buffer[N - 1]; }

  constexpr const_reference back() const noexcept { return m_buffer[N - 1]; }

  constexpr pointer data() noexcept { return m_buffer; }

  constexpr const_pointer data() const noexcept { return m_buffer; }

  friend std::ostream& operator<<(std::ostream& os, const array<value_type, N>& arr) {
    os << "[";
    for (int i = 0; i < N - 1; i++) {
      os << arr.at(i) << ", ";
    }
    os << arr.at(N - 1) << "]";
    return os;
  }

 private:
  value_type m_buffer[N];
};

template <typename T>
using pair = array<T, 2>;

#endif

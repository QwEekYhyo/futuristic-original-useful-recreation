#ifndef ARRAY_HPP
#define ARRAY_HPP

#include <iostream>

template <typename T, int N>
class array {
public:
  array() = default;

  array(const array<T, N>& original) {
      fill(original);
  }

  array(std::initializer_list<T> l) {
      int i = 0;
      for (const auto& element : l) {
        m_buffer[i] = element;
        i++;
      }
  }

  T& at(int index) {
    // TODO: Bound check
    return m_buffer[index];
  }

  const T& at(int index) const {
    return m_buffer[index];
  }

  void fill(const array<T, N>& other) {
    for (int i = 0; i < N; i++)
      m_buffer[i] = other.m_buffer[i];
  }

  friend std::ostream& operator<<(std::ostream& os, const array<T, N>& arr) {
      os << "[" ;
      for (int i = 0; i < N - 1; i++) {
          os << arr.at(i) << ", ";
      }
      os << arr.at(N - 1) << "]";
      return os;
  }

private:
  T m_buffer[N];
};

template <typename T>
using pair = array<T, 2>;

#endif

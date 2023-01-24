#ifndef ARRAY_HPP
#define ARRAY_HPP

template <typename T, int N>
class array {
public:
  array() = default;

  array(const array<T, N>& original) {
      fill(original);
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

private:
  T m_buffer[N];
};

#endif

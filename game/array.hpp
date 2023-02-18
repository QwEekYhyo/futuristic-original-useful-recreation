#ifndef ARRAY_HPP
#define ARRAY_HPP

#include "initializer_list.hpp"

template <typename T, int N>
class array {
    typedef T value_type;
    typedef value_type* pointer;
    typedef const value_type* const_pointer;
    typedef value_type& reference;
    typedef const value_type& const_reference;
    typedef size_t size_type;

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

    reference at(int index) {
      // TODO: Bound check
      return m_buffer[index];
    }

    const_reference at(int index) const {
      return m_buffer[index];
    }

    void fill(const array<value_type, N>& other) {
      for (int i = 0; i < N; i++)
        m_buffer[i] = other.m_buffer[i];
    }

    bool contains(value_type thing) {
      for (int i = 0; i < N; i++) {
        if (at(i) == thing) {
          return true;
        }
      }
      return false;
    }

    size_type size() const noexcept {
      return N;
    }
    size_type max_size() const noexcept {
      return N;
    }

    bool empty() const noexcept {
      return size() == 0;
    }

    reference operator[](size_type n) noexcept {
      return m_buffer[n];
    }

    const_reference operator[](size_type n) const noexcept {
      return m_buffer[n];
    }

    reference front() noexcept {
      return m_buffer[0];
    }

    const_reference front() const noexcept {
      return m_buffer[0];
    }

    reference back() noexcept {
      return m_buffer[N - 1];
    }

    const_reference back() const noexcept {
      return m_buffer[N - 1];
    }

    pointer data() noexcept {
      return m_buffer;
    }

    const_pointer data() const noexcept {
      return m_buffer;
    }

  private:
    value_type m_buffer[N];
};

template <typename T>
using pair = array<T, 2>;

#endif

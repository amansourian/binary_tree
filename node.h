//
// Created by Arman Mansourian on 10/17/18.
//

#ifndef BINARY_TREE_NODE_H
#define BINARY_TREE_NODE_H
#include <iostream>
#include <fstream>

enum NODE_CHILD {L, R};  // left child (L) and right child (R)

template<typename T>
struct node {
  // public member variables
  T m_data;
  int m_count;
  node<T>* p_child[2] = {nullptr, nullptr};

  // constructors and destructor
  explicit node(T data = T(), int count = 1) : m_data(data), m_count(count) {}
  node(const node<T> &other) : m_data(other.m_data), m_count(other.m_count) {}
  node<T>& operator=(const node<T> &other);
  ~node();

  node<T>& operator+=(const node<T> &other);  // increment count
  node<T>& operator-=(const node<T> &other);  // decrement count

  // friend comparison operators
  template<typename U>
  friend bool operator<(const node<U> &x, const node<U> &y);
  template<typename U>
  friend bool operator>(const node<U> &x, const node<U> &y);
  template<typename U>
  friend bool operator<=(const node<U> &x, const node<U> &y);
  template<typename U>
  friend bool operator>=(const node<U> &x, const node<U> &y);
  template<typename U>
  friend bool operator==(const node<U> &x, const node<U> &y);
  template<typename U>
  friend bool operator!=(const node<U> &x, const node<U> &y);

  // friend io operators
  template<typename U>
  friend std::ostream& operator<<(std::ostream& out, const node<U> &other);
  template<typename U>
  friend std::istream& operator>>(std::istream& in, node<U> &other);
};

template<typename T>
node<T>& node<T>::operator=(const node<T> &other) {
  if (this != &other) {
    m_data = other.m_data;
    m_count = other.m_count;
    p_child[L] = p_child[R] = nullptr;
  }
  return *this;
}

template<typename T>
node<T>::~node() {
  m_data = T();
  m_count = 0;
  p_child[L] = p_child[R] = nullptr;
}

template<typename T>
node<T>& node<T>::operator+=(const node<T> &other) {
  if (this != &other && m_data == other.m_data) m_count += other.m_count;
  return *this;
}

template<typename T>
node<T>& node<T>::operator-=(const node<T> &other) {
  if (this != &other && m_data == other.m_data) m_count -= other.m_count;
  return *this;
}

template<typename U>
bool operator<(const node<U> &x, const node<U> &y) {
  return x.m_data < y.m_data;
}

template<typename U>
bool operator>(const node<U> &x, const node<U> &y) {
  return x.m_data > y.m_data;
}

template<typename U>
bool operator<=(const node<U> &x, const node<U> &y) {
  return x.m_data <= y.m_data;
}

template<typename U>
bool operator>=(const node<U> &x, const node<U> &y) {
  return x.m_data >= y.m_data;
}

template<typename U>
bool operator==(const node<U> &x, const node<U> &y) {
  return x.m_data == y.m_data;
}

template<typename U>
bool operator!=(const node<U> &x, const node<U> &y) {
  return x.m_data != y.m_data;
}

template<typename U>
std::ostream& operator<<(std::ostream& out, const node<U> &n) {
  out << n.m_data << "[" << n.m_count << "] ";
  return out;
}

template<typename U>
std::istream& operator>>(std::istream& in, node<U> &n) {
  char junk = 0;
  if (&in == &std::cin) {
    std::cout << "data:  ";
    in >> n.m_data;
    std::cout << "count: ";
    in >> n.m_count;
  } else {
    in >> n.m_data >> junk >> n.m_count >> junk;
  }
  return in;
}

#endif // BINARY_TREE_NODE_H
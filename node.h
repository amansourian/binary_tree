#ifndef BINARY_TREE_NODE_H
#define BINARY_TREE_NODE_H
#include <iostream>
#include <fstream>

template<typename Data>
struct node {
  // members
  Data data{};
  int count{};
  node<Data> *left, *right;

  // constructors and destructor
  explicit node(Data d = Data(), int c = 1);
  ~node();                                          // destructor
  node(const node<Data> &other);                    // copy constructor
  node<Data>& operator=(const node<Data> &other);   // copy assignment operator
  node<Data>& operator+=(const node<Data> &other);

  // friend comparison operators
  template<typename D>
  friend bool operator==(const node<D> &x, const node<D> &y);
  template<typename D>
  friend bool operator!=(const node<D> &x, const node<D> &y);
  template<typename D>
  friend bool operator>=(const node<D> &x, const node<D> &y);
  template<typename D>
  friend bool operator<=(const node<D> &x, const node<D> &y);
  template<typename D>
  friend bool operator>(const node<D> &x, const node<D> &y);
  template<typename D>
  friend bool operator<(const node<D> &x, const node<D> &y);

  // friend io operators
  template<typename D>
  friend std::ostream& operator<<(std::ostream& out, const node<D> &other);
  template<typename D>
  friend std::istream& operator>>(std::istream& in, node<D> &other);
};

template<typename Data>
node<Data>::node(Data d, int c)
: data{d}, count{c}, left{nullptr}, right{nullptr} {}

template<typename Data>
node<Data>::node(const node<Data> &other)
: node(other.data, other.count) {}
//: data{other.data}, count{other.count}, left{nullptr}, right{nullptr} {}

template<typename Data>
node<Data>& node<Data>::operator=(const node<Data> &other) {
  if (this != &other) {
    data = other.data;
    count = other.count;
    left = right = nullptr;
  }
  return *this;
}

template<typename Data>
node<Data>& node<Data>::operator+=(const node<Data> &other) {
  if (this != &other && data == other.data) {
    count += other.count;
  }
  return *this;
}

template<typename Data>
node<Data>::~node() {
  data = Data();
  count = 0;
  left = right = nullptr;
}

template<typename D>
bool operator==(const node<D> &x, const node<D> &y) {
  return x.data == y.data;
}

template<typename D>
bool operator>=(const node<D> &x, const node<D> &y) {
  return x.data >= y.data;
}

template<typename D>
bool operator<=(const node<D> &x, const node<D> &y) {
  return x.data <= y.data;
}

template<typename D>
bool operator!=(const node<D> &x, const node<D> &y) {
  return x.data != y.data;
}

template<typename D>
bool operator>(const node<D> &x, const node<D> &y) {
  return x.data > y.data;
}

template<typename D>
bool operator<(const node<D> &x, const node<D> &y) {
  return x.data < y.data;
}

template<typename D>
std::ostream& operator<<(std::ostream& out, const node<D> &other) {
  out << other.data << "[" << other.count << "] ";
  return out;
}

template<typename D>
std::istream& operator>>(std::istream& in, node<D> &other) {
  char junk = 0;
  if (&in == &std::cin) {
    std::cout << "Data: ";
    in >> other.data;
    std::cout << "Count: ";
    in >> other.count;
  } else {
    in >> other.data >> junk >> other.count >> junk;
  }
  return in;
}

#endif // BINARY_TREE_NODE_H
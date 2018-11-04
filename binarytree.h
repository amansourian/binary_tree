//
// Created by Arman Mansourian on 10/17/18.
//

#ifndef BINARY_TREE_BINARYTREE_H
#define BINARY_TREE_BINARYTREE_H
#include <iostream>
#include <fstream>
#include "node.h"

enum BINARY_TREE_ERRORS {TREE_EMPTY, TREE_FULL};
enum BINARY_TREE_TRAVERSAL {IN_ORDER, PRE_ORDER, POST_ORDER};

template<typename T>
class BinaryTree {
public:
  // constructors and destructor
  BinaryTree() = default;
  explicit BinaryTree(node<T>* root) : p_root(root) {}
  BinaryTree(const BinaryTree<T> &other);
  BinaryTree<T>& operator=(const BinaryTree<T> &other);
  ~BinaryTree();

  // public member functions
  bool full() const;
  bool empty() const;
  bool contains(const T &data) const;
  unsigned int height() const;
  unsigned int dataCount() const;
  unsigned int nodeCount() const;
  BINARY_TREE_TRAVERSAL& traversal() const;

  void print() const;
  void insert(const T &data, int count = 1);
  void remove(const T &data, int count = 1);

  BinaryTree<T>& operator<<(const T &data); // insert operator

  // friend io functions
  template<typename U>
  friend std::ostream& operator<<(std::ostream& out, const BinaryTree<U> &tree);
  template<typename U>
  friend std::istream& operator>>(std::istream& in, BinaryTree<U> &tree);

private:
  // private member variables
  node<T>* p_root = nullptr;
  BINARY_TREE_TRAVERSAL m_method = IN_ORDER;

  // private helper functions
  bool contains(node<T>* n, const T &data) const;
  unsigned int height(node<T>* n) const;
  unsigned int dataCount(node<T>* n) const;
  unsigned int nodeCount(node<T>* n) const;

  void print(node<T>* n, const std::string &indent = "") const;
  void insert(node<T>* &n, const T &data, int count);
  void remove(node<T>* &n, const T &data, int count);

  node<T> getMin(node<T>* root) const;
  node<T>* find(const T &data, node<T>* root);
  void rebalance();

  // copy and delete
  void copy(node<T>* root);
  void deleteAll(node<T>* &root);
};

template<typename T>
BinaryTree<T>::BinaryTree(const BinaryTree<T> &other) {
  copy(other);
}

template<typename T>
BinaryTree<T>& BinaryTree<T>::operator=(const BinaryTree<T> &other) {
  if (this != &other) {
    deleteAll(p_root);
    copy(other);
  }
  return *this;
}

template<typename T>
BinaryTree<T>::~BinaryTree() {
  deleteAll(p_root);
}

template<typename T>
bool BinaryTree<T>::full() const {
  return false;  // for now, our tree can never be full
}

template<typename T>
bool BinaryTree<T>::empty() const {
  return !p_root;  // p_root == nullptr
}

template<typename T>
bool BinaryTree<T>::contains(const T &data) const {
  return contains(p_root, data);
}

template<typename T>
unsigned int BinaryTree<T>::height() const {
  return height(p_root);
}

template<typename T>
unsigned int BinaryTree<T>::dataCount() const {
  return dataCount(p_root);
}

template<typename T>
unsigned int BinaryTree<T>::nodeCount() const {
  return nodeCount(p_root);
}

template<typename T>
BINARY_TREE_TRAVERSAL& BinaryTree<T>::traversal() const {
  return m_method;
}

template<typename T>
void BinaryTree<T>::print() const {
  print(p_root);
}

template<typename T>
void BinaryTree<T>::insert(const T &data, int count) {
  insert(p_root, data, count);
}

template<typename T>
void BinaryTree<T>::remove(const T &data, int count) {
  remove(p_root, data, count);
}

template<typename T>
BinaryTree<T>& BinaryTree<T>::operator<<(const T &data) {
  insert(data);
  return *this;
}

template<typename T>
bool BinaryTree<T>::contains(node<T>* n, const T &data) const {
  // if pointer is null, there is no data
  if (!n) return false;

  // else check if data is here
  else if (data == n->m_data) return true;

  // else traverse recursively left and right until value is found
  else return contains(n->p_child[L], data) || contains(n->p_child[R], data);
}

template<typename T>
unsigned int BinaryTree<T>::height(node<T>* n) const {
  return !n ? 0 : 1 + max(height(n->p_child[L]), height(n->p_child[R]));
}

template<typename T>
unsigned int BinaryTree<T>::nodeCount(node<T>* n) const {
  return !n ? 0 : 1 + nodeCount(n->p_child[L]) + nodeCount(n->p_child[R]);
}

template<typename T>
unsigned int BinaryTree<T>::dataCount(node<T>* n) const {
  return !n ? 0 : n->m_count + dataCount(n->p_child[L]) + dataCount(n->p_child[R]);
}

template<typename T>
void BinaryTree<T>::print(node<T>* n, const std::string &indent) const {
  // if pointer is null, do nothing
  if (!n) return;

  // traverse right recursively and indent further
  print(n->p_child[R], indent + "    ");

  // print current node with indent
  std::cout << indent << n->m_data << '[' << n->m_count << ']' << std::endl;

  // traverse left recursively and indent further
  print(n->p_child[L], indent + "    ");
}

template<typename T>
void BinaryTree<T>::insert(node<T>* &n, const T &data, int count) {
  // if pointer is null, set to new node
  if (!n) n = new node<T>(data, count);

  // traverse left recursively
  else if (data < n->m_data) insert(n->p_child[L], data, count);

  // traverse right recursively
  else if (data > n->m_data) insert(n->p_child[R], data, count);

  // if data is identical, add to count
  else if (data == n->m_data) n->m_count += count;

  // rebalance();
}

template<typename T>
void BinaryTree<T>::remove(node<T>* &n, const T &data, int count) {
  if (!n) {}

  // if data we want to remove is smaller than n.data, traverse left
  else if (data < n->m_data) remove(n->p_child[L], data, count);

  // if data we want to remove is larger than n.data, traverse right
  else if (data > n->m_data) remove(n->p_child[R], data, count);

  // otherwise if data == n.data
  else {
    node<T>* junk = nullptr;

    // check if count after removal is > 0
    if (n->m_count - count > 0) n->m_count -= count;

    // if node is leaf
    else if (!n->p_child[L] && !n->p_child[R]) {
      std::cout << "HELLO" << std::endl;
      junk = n;
      n = nullptr;
    }
    // if node only has left child
    else if (!n->p_child[R]) {
      junk = n;
      n = n->p_child[L];
    }
    // if node only has right child
    else if (!n->p_child[L]) {
      junk = n;
      n = n->p_child[R];
    }
    // if node has two children, replace with min on right branch
    else {
      node<T> temp = getMin(n->p_child[R]);
      n->m_data = temp.m_data;
      n->m_count = temp.m_count;
      remove(n->p_child[R], temp.m_data, temp.m_count);
    }
    // deallocate memory!
    if (junk) delete junk;
  }
}

template<typename T>
node<T> BinaryTree<T>::getMin(node<T>* root) const {
  // empty tree has no min
  if (!root) throw BINARY_TREE_ERRORS(TREE_EMPTY);

  // traverse left until you reach the end
  if (!root->p_child[L]) return *root;
  else return getMin(root->p_child[L]);
}

template<typename T>
node<T>* BinaryTree<T>::find(const T &data, node<T>* root) {
  // base cases:
  if (!root || data == root->m_data) return root;

  // data is less than root's data
  if (data < root->m_data) return find(data, root->p_child[L]);

  // data is greater than root's data
  return find(data, root->p_child[R]);
}

template<typename T>
void BinaryTree<T>::rebalance() {
  // TODO: rebalance
}

template<typename T>
void BinaryTree<T>::copy(node<T>* root) {
  if (root) {  // r != nullptr
    insert(root->m_data, root->m_count);
    copy(root->p_left);
    copy(root->p_right);
  }
}

template<typename T>
void BinaryTree<T>::deleteAll(node<T>* &root) {
  if (root) {  // r != nullptr
    deleteAll(root->p_child[L]);
    deleteAll(root->p_child[R]);
    delete root;
    root = nullptr;
  }
}

template<typename U>
std::ostream& operator<<(std::ostream& out, const BinaryTree<U> &tree) {
  tree.print();
  return out;
}

template<typename U>
std::istream& operator>>(std::istream& in, BinaryTree<U> &tree) {
  node<U> temp;
  tree.deleteAllNodes(tree.p_root);
  while(in >> temp)
    tree.insertData(temp.m_data, temp.m_count);
  return in;
}

#endif // BINARY_TREE_BINARYTREE_H

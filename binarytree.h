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
  explicit BinaryTree(const T &data, int count = 1) : p_root{new node<T>(data, count)}, m_method{IN_ORDER} {}
  BinaryTree(const BinaryTree<T> &other);
  BinaryTree<T>& operator=(const BinaryTree<T> &other);
  ~BinaryTree();

  // checker functions
  bool full() const;
  bool empty() const;
  unsigned int height() const;
  unsigned int dataCount() const;
  unsigned int nodeCount() const;
  BINARY_TREE_TRAVERSAL& traversal() const;
  
  // insert and remove functions
  void deleteData(const T &data, int count = 1);
  void insertData(const T &data, int count = 1);
  BinaryTree<T>& operator<<(const T &data);

  // friend io functions
  template<typename U>
  friend std::ostream& operator<<(std::ostream& out, const BinaryTree<U> &t);
  template<typename U>
  friend std::istream& operator>>(std::istream& in, BinaryTree<U> &t);

private:
  // private members
  node<T>* p_root = nullptr;
  BINARY_TREE_TRAVERSAL m_method = IN_ORDER;

  // private functions
  unsigned int height(node<T>* n);
  unsigned int nodeCount(node<T>* n);
  unsigned int dataCount(node<T>* n);
  node<T>* find1(const T &d, node<T>* r, node<T>* &parent, bool &lessThan);
  node<T>* find2(const T &d, node<T>* r);
  node<T>* findLeftmostOnRightSide(node<T>* r);
  void deleteLeftNode(node<T>* &child,node<T>* parent);
  void deleteRightNode(node<T>* &child, node<T>* parent);
  void print(std::ostream &out, node<T>* r) const;

  // copy and delete
  void copy(node<T>* r);
  void deleteAllNodes(node<T>* &r);
};

template<typename T>
BinaryTree<T>::BinaryTree(const BinaryTree<T> &other) {
  copy(other);
}

template<typename T>
BinaryTree<T>& BinaryTree<T>::operator=(const BinaryTree<T> &other) {
  if (this != &other) {
    deleteAllNodes(p_root);
    copy(other);
  }
  return *this;
}

template<typename T>
BinaryTree<T>::~BinaryTree() {
  deleteAllNodes(p_root);
}

template<typename T>
bool BinaryTree<T>::full() const {
  return false;  // for now, our tree can never be full
}

template<typename T>
bool BinaryTree<T>::empty() const {
  return !p_root; // p_root == nullptr
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
void BinaryTree<T>::deleteData(const T &data, int count) {
  bool lessThan;
  node<T> *temp, *parent = nullptr, *child = find1(data, p_root, parent, lessThan);
  if (child) {
    if ((child->m_count -= count) < 1) {
      if (lessThan)
        deleteLeftNode(child, parent);
      else
        deleteRightNode(child, parent);
    }
  }
}

template<typename T>
void BinaryTree<T>::insertData(const T &data, int count) {
  auto newNode = new node<T>(data, count);
  if (empty()) {
    p_root = newNode;
  } else {
    bool cont = true;
    node<T>* insertPoint = p_root;
    while (insertPoint && cont) {
      if (*newNode == *insertPoint) {
        *insertPoint += *newNode;
        delete newNode;
        return;
      }
      if (*newNode < *insertPoint) {
        if (!insertPoint->p_left)
          cont = false;
        else
          insertPoint = insertPoint->p_left;
      } else {
        if (!insertPoint->p_right)
          cont = false;
        else
          insertPoint = insertPoint->p_right;
      }
    }
    if (*newNode < *insertPoint)
      insertPoint->p_left = newNode;
    else
      insertPoint->p_right = newNode;
  }
  // rebalance();
}

template<typename T>
BinaryTree<T>& BinaryTree<T>::operator<<(const T &data) {
  insertData(data);
  return *this;
}

template<typename T>
unsigned int BinaryTree<T>::height(node<T>* n) {
  return !n ? 0 : 1 + max(height(n->p_left), height(n->p_right));
//  return n == nullptr ? 0 : 1 + max(height(n.p_left), height(n.p_right));
}

template<typename T>
unsigned int BinaryTree<T>::nodeCount(node<T>* n) {
  return !n ? 0 : 1 + nodeCount(n->p_left) + nodeCount(n->p_right);
}

template<typename T>
unsigned int BinaryTree<T>::dataCount(node<T>* n) {
  return !n ? 0 : n->count + dataCount(n->p_right) + dataCount(n->p_left);
}

template<typename T>
node<T>* BinaryTree<T>::find1(const T &data, node<T>* r, node<T>* &parent, bool &lessThan) {
  parent = r;
  lessThan = true;
  bool cont = true;
  while (r && cont) {
    std::cout << "r contains: " << *r << std::endl;
    if (data < r->m_data) {
      parent = r;
      r = r->p_left;
    }
    if (data == r->m_data) {
      lessThan = r == parent->p_left;
      cont = false;
    }
    if (data > r->m_data) {
      parent = r;
      r = r->p_right;
    }
  }
  return r;
}

template<typename T>
node<T>* BinaryTree<T>::find2(const T &data, node<T>* r) {
  // Base Cases: p_root is null or key is present at p_root
  if (r == nullptr || r->m_data == data) {
    return r;
  }
  // Key is greater than p_root's key
  if (r->m_data < data) {
    return find(data, r->p_right);
  }
  // Key is smaller than p_root's key
  return find(data, r->p_left);
}

template<typename T>
node<T>* BinaryTree<T>::findLeftmostOnRightSide(node<T>* r) {
  node<T>* temp = r->p_right;
  for (; temp->p_left != nullptr; temp = temp->p_left);
  return temp;
}

template<typename T>
void BinaryTree<T>::deleteLeftNode(node<T>* &child, node<T>* parent) {
  node<T>* temp;
  if (child->p_right) {
    parent->p_left = child->p_right;
    findLeftmostOnRightSide(child->p_right)->p_left = child->p_left;
    delete child;
  }
  else {
    parent->p_left = child->p_left;
    delete child;
  }
}

template<typename T>
void BinaryTree<T>::deleteRightNode(node<T>* &child,node<T>* parent) {
  node<T>* temp;
  if (parent == p_root) {
    if (p_root->p_right) {
      p_root = p_root->p_right;
      temp = findLeftmostOnRightSide(p_root);
      temp->p_left = parent->p_left;
      delete parent;
    } else {
      p_root = p_root->p_left;
      delete parent;
    }
  } else {
    if (child->p_right) {
      parent->p_right = child->p_right;
      temp = findLeftmostOnRightSide(child->p_right);
      temp->p_left = child->p_left;
      delete child;
    } else {
      parent->p_left = child->p_left;
      delete child;
    }
  }
}

template<typename T>
void BinaryTree<T>::print(std::ostream &out, node<T>* r) const {
  if (r) {  // r != nullptr
    if (m_method == PRE_ORDER)
      out << *r;
    print(out, r->p_left);
    if (m_method == IN_ORDER)
      out << *r;
    print(out, r->p_right);
    if (m_method == POST_ORDER)
      out << *r;
  }
}

template<typename T>
void BinaryTree<T>::copy(node<T>* r) {
  if (r) {  // r != nullptr
    insertData(r->m_data, r->m_count);
    copy(r->p_left);
    copy(r->p_right);
  }
}

template<typename T>
void BinaryTree<T>::deleteAllNodes(node<T>* &r) {
  if (r) {  // r != nullptr
    deleteAllNodes(r->p_left);
    deleteAllNodes(r->p_right);
    delete r;
    r = nullptr;
  }
}

template<typename U>
std::ostream& operator<<(std::ostream& out, const BinaryTree<U> &tree) {
  tree.print(out, tree.p_root);
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

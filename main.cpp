//
// Created by Arman Mansourian on 10/17/18.
//

#include <iostream>
#include <random>
#include "binarytree.h"
using namespace std;

default_random_engine& getEngine();
uniform_int_distribution<unsigned int>& getRandomInt(const unsigned int &min, const unsigned int &max);

int main() {
  // initialize random number generator
  default_random_engine engine = getEngine();
  uniform_int_distribution<unsigned int> rand_int = getRandomInt(0, 9);

  // vars
  BinaryTree<int> tree;
  int data;
  int count = 0;

  // begin test
  try {
    cout << "Starting!!!" << endl;
    for (size_t i = 0; i < 100; ++i) {
      data = rand_int(engine);
      cout << "Just input: " << data << endl;
      tree << data;
      if (data == 5) ++count;
    }

    cout << "Your tree: " << endl << endl << tree << endl << endl;
    for (size_t i = 0; i < 25; ++i) {
      data = rand_int(engine);
      cout << "Trying to remove: " << data << endl;
      tree.remove(data);
    }
    cout << "Your tree: " << endl << endl << tree << endl << endl;

  } catch (BINARY_TREE_ERRORS e) {
    switch (e) {
      case TREE_FULL: cout << "ERROR: Tree Full..." << endl; break;
      case TREE_EMPTY: cout << "ERROR: Tree Empty..." << endl; break;
    }
  } catch (...) {
    cout << "Unknown Error..." << endl;
  }
  // end test

  return 0;
}

default_random_engine& getEngine() {
  static default_random_engine engine(static_cast<unsigned int>(time(nullptr)));
  return engine;
}

uniform_int_distribution<unsigned int>& getRandomInt(const unsigned int &min, const unsigned int &max) {
  static uniform_int_distribution<unsigned int> random_int(min, max);
  return random_int;
}

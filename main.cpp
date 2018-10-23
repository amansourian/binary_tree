#include <iostream>
#include <random>
#include "binarytree.h"
using namespace std;

default_random_engine& getEngine();
uniform_int_distribution<unsigned int>& getRandomInt(const unsigned int &min, const unsigned int &max);

int main() {
  // initialize random number generator
  default_random_engine engine = getEngine();
  uniform_int_distribution<unsigned int> randInt = getRandomInt(0, 9);

  // vars
  int data;
  BinaryTree<int> tree;

  // begin test
  cout << "Starting!!!" << endl;
  for (size_t i = 0; i < 25; ++i) {
    data = randInt(engine);
    cout << "Just input: " << data << endl;
    tree << data;
  }
  cout << "Your tree contains: " << tree << endl << endl;
  for (size_t i = 0; i < 25; ++i) {
    data = randInt(engine);
    cout << "Trying to delete: " << data << endl;
    tree.deleteData(data);
  }
  cout << "Your tree contains: " << tree << endl << endl;
  // end test

  return 0;
}

default_random_engine& getEngine() {
  static default_random_engine engine(static_cast<unsigned int>(time(nullptr)));
  return engine;
}

uniform_int_distribution<unsigned int>& getRandomInt(const unsigned int &min, const unsigned int &max) {
  static uniform_int_distribution<unsigned int> randomInt(min, max);
  return randomInt;
}

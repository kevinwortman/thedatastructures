
#include <cassert>
#include <cstdlib>
#include <iostream>

#include "linked_deque.hh"
#include "circular_array_deque.hh"

using namespace std;

int random_2_digit() {
  return rand() % 100;
}

int main() {

  const int N = 12, SEED = 0xDEADC0DE;

  assert((N % 2) == 0);

  srand(SEED);

  cout << "LinkedDeque:" << endl;
  LinkedDeque<int> linked;
  for (int i = 0; i < N/2; ++i) {
    int a = random_2_digit(), b = random_2_digit();
    cout << "adding "
	 << a << " to front and "
	 << b << " to back" << endl;
    linked.add_front(a);
    linked.add_back(b);
  }
  cout << "size is " << linked.size() << endl;
  while (!linked.is_empty()) {
    cout << "removing " << linked.front() << " from front";
    linked.remove_front();
    cout << ", new size is " << linked.size() << endl;
  }
  cout << endl;

  cout << "CircularArrayDeque:" << endl;
  CircularArrayDeque<int> circular(N);
  for (int i = 0; i < N/2; ++i) {
    int a = random_2_digit(), b = random_2_digit();
    cout << "adding "
	 << a << " to front and "
	 << b << " to back" << endl;
    circular.add_front(a);
    circular.add_back(b);
  }
  cout << "size is " << circular.size() << endl;
  while (!circular.is_empty()) {
    cout << "removing " << circular.front() << " from front";
    circular.remove_front();
    cout << ", new size is " << circular.size() << endl;
  }
  cout << endl;

  return 0;
}

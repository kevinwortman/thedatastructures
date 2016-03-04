
#include <cassert>
#include <cstdlib>
#include <iostream>

#include "dequeues.hh"

using namespace std;

int random_2_digit() {
  return rand() % 100;
}

int main() {

  const int N = 12, SEED = 0xDEADC0DE;

  assert((N % 2) == 0);

  srand(SEED);

  CircularArrayDequeue<int> circular(N);
  LinkedDequeue<int> linked;
  
  cout << "Adding to dequeues...";
  for (int i = 0; i < (N/2); ++i) {
    int a = random_2_digit(), b = random_2_digit();
    cout << "adding "
	 << a << " to front and "
	 << b << " to back" << endl;
    circular.add_front(a);
    linked.add_front(a);
    circular.add_back(b);
    linked.add_back(b);
  }

  cout << endl
       << "sizes: " << circular.size() << " and " << linked.size() << endl;
  assert(12 == circular.size());
  assert(12 == linked.size());

  cout << "removing from front of circular dequeue:";
  while (!circular.is_empty()) {
    cout << circular.front() << " ";
    circular.remove_front();
  }

  cout << endl
       << "removing from back of linked dequeue:";
  while (!linked.is_empty()) {
    cout << linked.back() << " ";
    linked.remove_back();
  }

  cout << endl;

  return 0;
}

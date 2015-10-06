
#include <iostream>

#include "dynamic_vector.hh"

using namespace std;

int main() {

  const int N = 10*1000*1000; // 10 million

  cout << "Creating dynamic vector with 10 million elements..." << endl;
  DynamicVector<int> vect;
  for (int i = 0; i < N; i++)
    vect.add_back(i);

  cout << "Checking contents..." << endl;
  for (int i = 0; i < N; i++)
    assert(vect.get(i) == i);

  cout << "Removing elements one a time from the back..." << endl;
  while (!vect.is_empty())
    vect.remove_back();

  cout << "Adding elements back in..." << endl;
  for (int i = 0; i < N; i++)
    vect.add_back(i);

  cout << "clearing..." << endl;
  vect.clear();

  return 0;
}

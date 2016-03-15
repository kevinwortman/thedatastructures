
#include <iostream>

#include "dynamic_vector.hh"

using namespace std;

int main() {

  const int N = 10*1000*1000; // 10 million

  {
    DynamicVector<int> vect;

    cout << "Creating dynamic vector with 10 million elements..." << endl;
    for (int i = 0; i < N; i++) {
      vect.add_back(i);
    }

    cout << "Checking contents..." << endl;
    for (int i = 0; i < N; i++) {
      assert(vect.get(i) == i);
    }

    cout << "clear()..." << endl;
    vect.clear();

    cout << "Adding elements back in..." << endl;
    for (int i = 0; i < N; i++) {
      vect.add_back(i);
    }

    cout << "Iterator..." << endl;
    for (auto i = DynamicVectorIterator<int>(&vect); !i.past_end(); i.advance()) {
      static int j = 0;
      assert(i.get() == j);
      j++;
    }
    
    cout << "destructor..." << endl;
  }

  return 0;
}

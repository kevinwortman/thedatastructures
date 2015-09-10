
#include <iostream>

#include "exceptions.hh"

using namespace std;

int main() {
  try {
    cout << "Get ready for an exception..." << endl;
    throw IndexException(-1, 5);
  } catch (IndexException e) {
    cout << "Exception: bad index " << e.index() << endl;
  }

  return 0;
}

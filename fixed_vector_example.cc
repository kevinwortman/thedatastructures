
#include <iostream>

#include "fixed_vector.hh"

using namespace std;

int main() {

  const int N = 10;

  cout << "Generating the first " << N << " perfect squares...";
  FixedVector<int> squares(N);
  for (int i = 0; i < N; i++)
    squares.set(i, i * i);

  cout << "done" << endl << "They are:" << endl;
  for (int i = 0; i < N; i++)
    cout << "    " << squares.get(i) << endl;

  cout << endl << "Do exceptions work? ";
  bool exception_happened = false;
  try {
    squares.get(-1);
  } catch (IndexException e) {
    exception_happened = true;
  }
  if (exception_happened) {
    cout << "yes";
  } else {
    cout << "no";
  }
  cout << endl;
  
  return 0;
}

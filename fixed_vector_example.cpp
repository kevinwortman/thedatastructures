
#include <cassert>

#include "fixed_vector.hh"

int main() {

  // basic operation on a short vector
  FixedVector<int> v(8, 123);
  assert(8 == v.length());
  assert(!v.is_empty());
  assert(123 == v.get(0));
  assert(123 == v.get(7));
  v.set(5, 55);
  assert(55 == v.get(5));

  // empty vectors work
  FixedVector<double> empty1(0, 0.0), empty2;
  assert(empty1.is_empty());
  assert(empty2.is_empty());
  assert(0 == empty1.length());
  assert(0 == empty2.length());
  
  // iterator
  bool iterated = false;
  int total = 0;
  for (FixedVectorIterator<int> i(&v); !i.past_end(); i.advance()) {
    iterated = true;
    total += i.get();
  }
  assert(iterated);
  assert(total == (7*123 + 55));
  iterated = false;
  for (FixedVectorIterator<double> i(&empty1); !i.past_end(); i.advance()) {
    iterated = true;
  }
  assert(!iterated);  
  
  return 0;
}


#pragma once

template <typename LEFT, typename RIGHT>
class Pair {
public:
  Pair(LEFT left, RIGHT right)
    : _left(left),
      _right(right) { }

  LEFT left()   { return _left;  }
  RIGHT right() { return _right; }
  
  void set_left(LEFT left)    { _left = left;   }
  void set_right(RIGHT right) { _right = right; }
  
private:
  LEFT _left;
  RIGHT _right;
};

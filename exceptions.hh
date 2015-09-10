
#pragma once

#include <string>

// Invalid array index: either negative, or greater than or equal to
// the array length.
class IndexException {
public:
  IndexException(int length, int index)
    : _length(length),
      _index(index) { }

  int length() { return _length; }
  int index()  { return _index;  }

private:
  int _length, _index;
};

// Invalid argument passed to a function.
class ArgumentException {
public:
  ArgumentException(std::string& description)
    : _description(description) { }

  ArgumentException(const char* c_string)
    : _description(c_string) { }

  std::string& description() { return _description; }

private:
  std::string _description;
};

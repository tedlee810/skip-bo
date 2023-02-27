#include "Card.h"

#include <iostream>
#include <string>

using std::cout;
using std::string;
using std::to_string;

Card::Card(const Card& rhs) {
  value = rhs.value;
}

void Card::operator=(const Card& rhs) {
  value = rhs.value;
}

void Card::display() const {
  cout << "[";
  if (value == 0) {
    cout << "SB";
  } else {
    cout << value;
  }
  cout << "]";
}

string Card::toString() const { 
  return to_string(value);
}


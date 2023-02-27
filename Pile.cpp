#include "Pile.h"

#include <iostream>
#include <vector>
#include <string>
#include <istream>

using std::string;
using std::to_string;
using std::istream;

Pile::Pile(const Pile& rhs) {
  for (int i = 0; i < rhs.size(); i++) {
    Card temp(rhs.pile.at(i).getValue());
    pile.push_back(temp);
  }
}

Pile::~Pile() {
  pile.clear();
  pile.shrink_to_fit();
}

Pile& Pile::operator=(const Pile& rhs) {
  pile = rhs.pile;
  return *this;
}

void Pile::addPile(Pile& clearPile) {
  // iterate through clearPile until all Cards are added
  while (clearPile.size() != 0)
    pile.insert(pile.begin(), clearPile.popCard());
}

Card Pile::popCard() {
  // get the value of the top Card in the Pile and pop
  int val = pile[pile.size() - 1].getValue();
  pile.pop_back();

  // return a new Card with that value
  return Card(val);
}

string Pile::toString() const {
  string result;
  result.append(to_string(size()));
  result.append("\n");
  // add all the pile elements to the string, at most 20 per line
  for (int i = 0; i < size(); ++i) {
    if (i % 20 == 0 && i != 0)
      result.append("\n");
    else if (i != 0)
      result.append(" ");
    result.append(pile[i].toString());
  }
  result.append("\n");
  return result;
}

void Pile::readIn(istream& is) {
  // get the data from the saved game file
  string typeOfPile;
  int size, cardVal;

  // read in the Pile type and its size
  is >> typeOfPile >> size;

  // create and add Cards to the Pile
  for (int i = 0; i < size; i++) {
    is >> cardVal;
    Card temp(cardVal);
    addCard(temp);
  }
}

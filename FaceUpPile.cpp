#include "FaceUpPile.h"

#include <iostream>

using std::cout;

FaceUpPile::FaceUpPile(const FaceUpPile& rhs) : Pile() {
  for (int i = 0; i < rhs.size(); i++) {
    Card temp(rhs.pile.at(i).getValue());
    pile.push_back(temp);
  }
}

//returns the value of the top card
int FaceUpPile::getTopCard() {
  if (pile.size()) {
    return pile[pile.size() - 1].getValue();
  }
  return -1; // empty pile
}

// for live game play - must not change!
void FaceUpPile::display() const {
  if (size()) {
    pile[pile.size() - 1].display();
  }
  else cout << "--";
  cout << "/" << size();
}


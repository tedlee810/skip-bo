#include "Hand.h"

#include <iostream>
#include <string>

using std::cout;
using std::string;
using std::to_string;

Hand::~Hand() {
  hand.clear();
  hand.shrink_to_fit();
}

Card Hand::popCard(int pos) {
  // store the value of the card to be popped
  int val = hand[pos].getValue();

  // delete the Card and return a new Card of that value
  hand.erase(hand.begin() + pos);
  return Card(val);
}

void Hand::replenish(DrawPile& draw) {
  // number of remaining cards to draw
  int cardsToAdd = 5 - hand.size();
  for (int i = 0; i < cardsToAdd; i++) {
    hand.push_back(draw.popCard());
  }
}

string Hand::toString() const {
  string result;
  result.append(to_string(size()));
  result.append("\n");
  for (int i = 0; i < size(); ++i) {
    if (i % 20 == 0 && i != 0) {
      result.append("\n");
    } else if (i != 0) {
      result.append(" ");
    }
    result.append(hand[i].toString());
  }
  result.append("\n");
  
  return result;
}

void Hand::display() const {
  int i;
  for (i = 0; i < size(); i++) {
    hand[i].display();
    cout << "  ";
  }
  for ( ; i < 5; i++)
    cout << "--  ";
}

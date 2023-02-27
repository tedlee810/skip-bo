#include "Player.h"

#include <iostream>
#include <string>
#include <vector>
#include <sstream>
#include <istream>

using std::string;
using std::stringstream;
using std::vector;
using std::cin;
using std::cout;
using std::endl;
using std::istream;

Player::Player(string playerName) : name(playerName) {
  // create 4 empty discard piles
  for (int i = 0; i < 4; i++) {
    FaceUpPile temp;
    discard.push_back(temp);
  }
}

Player::~Player() {
  discard.clear();
  discard.shrink_to_fit();
}

int Player::stockMove(int dest, vector<FaceUpPile>& build) {
  // get the top Card's value and move it to the build pile
  int cardVal = stock.getTopCard();
  if (cardVal == 0 || cardVal == build[dest].size() + 1) {
    build[dest].addCard(stock.popCard());
    return 1;
  }
  return 0;
}

int Player::discardMove(int orig, int dest, std::vector<FaceUpPile>& build) {
  int pos = orig - 1;
  // make sure that the desired discard pile we're moving a card from actually has a card
  if (discard[pos].size() != 0) {
    int cardval = discard[pos].getTopCard();
    // starting a build pile
    if (cardval == 1 && build[dest].size() == 0) {
      build[dest].addCard(discard[pos].popCard());
      return 1;
    } else if (cardval == 0 || cardval == build[dest].size() + 1) {
      build[dest].addCard(discard[pos].popCard());
      return 1;
    }
  }
  return 0;
}

int Player::handMove(int orig, int dest, std::vector<FaceUpPile>& build) {
  int pos = orig - 5;
  int cardval = hand.getCard(pos);
  if (pos >= hand.size()) {
    return 0;
  } else {
    // moving to a build pile
    if (dest < 10) {
      // starting a build pile
      if (cardval == 1 && build[dest].size() == 0) {
	build[dest].addCard(hand.popCard(pos));
	return 1;
	//adding a wild card or sequentially
      } else if (cardval == 0 || cardval == build[dest].size() + 1) {
	build[dest].addCard(hand.popCard(pos));
	return 1;
      }
    } else if (dest >= 10) {
      dest -= 10;
      discard[dest].addCard(hand.popCard(pos));
      return 2;
    }
  }
  return 0;
}

// for live game play - must not change!
void Player::display() const {
  cout << "Current ";
  cout << name << ":  Stock{0}: " ;
  stock.display();
  cout << endl;
  cout << "   Discards{1-4}: ";
  for (int i = 0; i < 4; ++i) {
    discard[i].display();
    cout << "  ";
  }
  cout << endl;
  cout << "   Hand{5-9}: ";
  hand.display();
  cout << endl;
}

/* saving state format - must not change!
PlayerName
Stock size
01 02 03  ...
...
Hand size
01 02 03 04 05
Discard1 size
01 02 03 04 ...
...
Discard2 size
...
Discard3 size
...
Discard4 size
...
*/
string Player::toString() const {
  stringstream result;
  result << name << "\n";
  result << "Stock " << stock.toString();

  //TESTING
  result << "Hand " << hand.toString();
  
  for (int i = 0; i < 4; ++i) {
    result << "Discard" << i << " " << discard[i].toString();
  }
  return result.str();
}

void Player::readIn(istream& is) {
  stock.readIn(is);
      
  // get the cards in "hand"
  // TODO: move this all into Hand::readIn (friend class for Pile?)
  
  string handString;
  int handSize;
  is >> handString >> handSize;

  int cardVal;
  for (int i = 0; i < handSize; i++) {
    is >> cardVal;
    Card temp(cardVal);
    hand.addCard(temp);
  }
  
  // read player's discard data
  for (int i = 0; i < 4; i++) {
    discard[i].readIn(is);
  }
}

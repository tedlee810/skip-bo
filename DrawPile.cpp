#include "DrawPile.h"

#include <iostream>
#include <fstream>
#include <string>
#include <algorithm>
#include <ctime>

using std::string;
using std::ifstream;
using std::srand;
using std::time;
using std::random_shuffle;
using std::cout;

DrawPile::DrawPile(bool shuffle, string filename) : isShuffled(shuffle) {
  ifstream deckFile(filename);
  int temp;
  while (deckFile >> temp) {
    Card newCard(temp);
    pile.push_back(newCard);
  }
  helpShuffle(shuffle);
}

void DrawPile::helpShuffle(bool shuffle){
  if (shuffle) {
    srand(time(NULL));
    random_shuffle(pile.begin(), pile.end());
  }
}

string DrawPile::getRand() const {
  if (isShuffled) {
    return "true";
  }  
  return "false";
}

void DrawPile::display() const {
  cout << "[XX]/" << size();
}

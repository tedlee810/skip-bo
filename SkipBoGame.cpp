#include "SkipBoGame.h"

#include <iostream>
#include <sstream>
#include <cstdlib>
#include <ctime>
#include <string>
#include <sstream>
#include <istream>

using std::ifstream;
using std::string;
using std::to_string;
using std::stringstream;
using std::srand;
using std::time;
using std::cout;
using std::cin;
using std::endl;
using std::istream;

/** 
 * Prints statement for illegal argument.
 */
void illegalCommand() {
  cout << "illegal command, try again" << endl << endl;
}

SkipBoGame::SkipBoGame(int numPlayers, bool isShuffled, int stockSize, string deckFile) :
  nump(numPlayers), draw(isShuffled, deckFile), sizeStock(stockSize) {

  // create 4 empty build piles
  for (int i = 0; i < 4; i++) {
    FaceUpPile temp;
    build.push_back(temp);
  }

  // create 4 players (Player0, Player1, ...)
  for (int i = 0; i < numPlayers; i++) {
    string name = "Player" + to_string(i);
    Player a(name);
    peep.push_back(a);
  }

  // distribute to stock pile
  for (int i = 0; i < stockSize; i++) {
    for (int j = 0; j < numPlayers; j++) {
      peep[j].addToStock(draw.popCard());
    }
  }

  // check for shuffled state
  if (isShuffled) {
    srand(time(NULL)); // use random generator
    curp = rand() % numPlayers; // generate random player to start
  } else {
    curp = 0; // start with Player0
  }
}

SkipBoGame::SkipBoGame(string loadFile, bool isShuffled) : draw(isShuffled) {
  // create ifstream for save file to load from and read data
  ifstream loadGame(loadFile);
  readIn(loadGame);

  // for printing purposes later
  sizeStock = peep[curp].stock.size();

  // shuffle game if indicated
  if (isShuffled)
    draw.helpShuffle(isShuffled);
}

SkipBoGame::~SkipBoGame() {
  peep.clear();
  peep.shrink_to_fit();
  build.clear();
  build.shrink_to_fit();
}

void SkipBoGame::nextPlayer() {
  // check if the current Player is the last in the vector as to not go out of bounds
  if (curp + 1 == (int) peep.size())
    curp = 0;
  // increment as normal
  else
    curp++;
}

void SkipBoGame::addToDraw() {
  // iterate through storedBuild and add to the draw pile
  for (int i = (int) storedBuild.size() - 1; i > -1; i--)
    draw.addPile(storedBuild.at(i));
  
  // check if shuffle state is true
  if (draw.getRand() == "true")
    draw.helpShuffle(true);
}

int SkipBoGame::determineDest(char charDest) {  
  int dest;

  // returns 0-3 for build piles a-d
  if (charDest == 'a') {
    dest = 0;
  } else if (charDest == 'b') {
    dest = 1;
  } else if (charDest == 'c') {
    dest = 2;
  } else if (charDest == 'd') {
    dest = 3;
  }

  // returns 10-13 for discard piles 1-4
  else if (charDest == '1') {
    dest = 10;
  } else if (charDest == '2') {
    dest = 11;
  } else if (charDest == '3') {
    dest = 12;
  } else if (charDest == '4') {
    dest = 13;
  }

  // returns -1 for invalid destination
  else {
    dest = -1;
  }
  return dest;
}

int SkipBoGame::getMove(char& act, char& charDest, int& orig, int& dest) {
  string input;    // gets the user input
  string command;  // final string representing the command
  int counter = 0; // amount of times parsed from input

  // get user input
  while (cin >> input) {
    counter++; // increment counter every time something is parsed
    command += input; // concantenate input to command

    // inputted action is draw
    if (command.at(0) == 'd') {
      act = command.at(0);
      break;
    }
    // stop accepting input once 3 inputs are made (e.g. "m 0 a")
    if (command.size() == 3)
      break;
  }

  // user inputs EOF
  if (cin.eof())
    return -1;
  
  // check for no spaces (e.g. "m0a"); illegal move if so
  if (command.size() == 3 && counter != 3) {
    illegalCommand();
    return 0;
  }
  // check if action was to move a card
  else if (command.at(0) == 'm') {
    act = command.at(0);           // getting the action (e.g. 'm')
    char charOrig = command.at(1); // getting the origin of card (e.g. '0')
    charDest = command.at(2);      // getting the destination (e.g. 'a')
    
    // make sure that charOrig is a valid number by checking ASCII values
    if (charOrig < 48 || charOrig > 57) {
      illegalCommand();
      return 0;
    } else {
      // get integer versions of orig and dest
      orig = (int) charOrig - 48;
      dest = determineDest(charDest);
      // ensure dest is a valid location
      if (dest == -1) {
	illegalCommand();
	return 0;
      }
    }
  }  
  return 1; // input successfully parsed
}

void SkipBoGame::makeMove(bool& continueGame) {
  // replenish hand before every turn
  peep[curp].hand.replenish(draw);

  // iterate through player's turn until their stock size is empty (i.e. wins)
  while (peep[curp].stock.size() != 0) {
    // print the game contents at the beginning of every move
    this->display();

    // if draw pile is empty, replenish
    if (draw.size() == 0)
      addToDraw();

    // act      = user-chosen action ('m'/'e'/'d')
    // charDest = user-chosen destination of card
    // orig     = integer representation of charOrig
    // dest     = integer representation of charDest
    char act, charDest;
    int orig = -1;
    int dest = -1;

    // check if the input is valid
    cout << "(m)ove [start] [end] or (d)raw ? ";
    int validInput = getMove(act, charDest, orig, dest);

    // if move is invalid (i.e. validMove == 0), move to next iteration
    if (validInput == 0)
      continue;

    // if user inputs EOF (i.e. validMove == -1), break out of the while loop
    if (validInput == -1) {
      cout << "thanks for playing" << endl;
      continueGame = false;
      break;
    }

    // keeps track of whether a move is valid or not

    // move values:
    //   0: invalid (default)
    //   1: valid
    //   2: end turn
    int move = 0;

    // check if player wants to draw
    if (act == 'd') {
      // if hand is empty, replenish it
      if (peep[curp].hand.size() == 0) {
	peep[curp].hand.replenish(draw);
	move = 1;
      }
    }

    // check if player wants to move a card
    else if (act == 'm') {
      // NOTE: values of dest greater than 10 are reserved for discard piles

      // card comes from stock pile
      if (orig == 0)
	dest < 10 ? move = peep[curp].stockMove(dest, build) : move = 0;

      // card comes from discard pile
      else if (orig >= 1 && orig <= 4)
	dest < 10 ? move = peep[curp].discardMove(orig, dest, build) : move = 0;

      // card comes from hand
      else if (orig >= 5 && orig <= 9) {
	move = peep[curp].handMove(orig, dest, build);
	// end of player's turn
	if (move == 2) {
	  cout << endl;
	  this->display();
	  cout << endl;
	  break;
	}
      }
    }

    // invalid move
    if (move == 0) {
      illegalCommand();
      continue;
    }
    // stock is empty (i.e. player wins)
    else if (peep[curp].stock.size() == 0) {
      continueGame = false;
      cout << endl;
      getWinner();
      break;
    }
    // move card to build pile, checking if it's full
    else if (dest >= 0 && dest <= 3) {
      // 12 is max build pile size
      if (build[dest].size() == 12) {
	cout << "build pile " << charDest << " full, set aside" << endl;

	// create deep copy of build and push into storedBuild
	FaceUpPile asidePile(build[dest]);
	storedBuild.push_back(asidePile);

	// clear the build pile vector
	build[dest].clear();
      }
    }
    cout << endl;
  }
}

void SkipBoGame::getWinner() {
  cout << "GAME OVER - " << peep.at(curp).getName() << " wins!" << endl;
}

/* for saving state - must not change format!

shuffle numPlayers currplayer
PlayerCurp [display]
PlayerCurp+1 [display]
[etc for all players]
Draw [display]
Build_a [display]
Build_b [display]
Build_c [display]
Build_d [display]
*/
string SkipBoGame::toString() const {
  stringstream result;
  int idx;

  string playerName = peep[curp].getName();
  string playerNum = playerName.substr(6, 6);
  int currentPlayer = stoi(playerNum);
  
  result << draw.getRand() << " " << nump << " " << currentPlayer << "\n";
  for (int i = 0; i < nump; ++i) {
    idx = (curp + i) % nump;
    result << peep[idx].toString();
  }
  result << "Draw " << draw.toString(); 
  for (int j = 0; j < 4; j++) {
    result << "Build_" << char('a'+j) << " ";
    result << build[j].toString();  
  }
  return result.str();
}

void SkipBoGame::readIn(istream& is) {
  // indicates whether shuffled or not
  string shuffleState;

  // set current player to 0 (whoever is in the first element of peep)
  curp = 0;

  // indicates starting player from file
  int fpnum;
  is >> shuffleState >> nump >> fpnum;

  // read player data
  for (int i = 0; i < nump; i++) {
    // read the player name
    string playerName;
    is >> playerName;
    
    //create a player and add to the 'peep' player vector
    Player temp(playerName);
    temp.readIn(is);
    peep.push_back(temp);
  }

  // read draw pile data
  draw.readIn(is);

  // read build pile data
  for (int i = 0; i < 4; i++) {
    FaceUpPile buildTemp;
    buildTemp.readIn(is);
    build.push_back(buildTemp);
  }
}

/* for live game play - must not change format!

drawPile  build_a  build_b  build_c  build_d
playerName  stock_0  
discards: discard_1 discard_2 discard_3 discard_4
hand: card_5 card_6 card_7 card_8 card_9
*/
void SkipBoGame::display() const {
  cout << "Draw: ";
  draw.display();
  cout << "  Build Piles: ";
  for (int j = 0; j < 4; j++) {
    build[j].display();
    cout << " ";
  }
  cout << endl;
  peep[curp].display();
}

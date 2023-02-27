#include "SkipBoGame.h"

#include <cstdlib>
#include <cstdio>
#include <iostream>
#include <string>

using std::cin;
using std::cout;
using std::endl;
using std::string;
using std::ifstream;
using std::ofstream;

/**
 * Checks for shuffled state.
 *
 * @param shuffleState is the cmd-line arg of whether deck is shuffled or not
 * @param isShuffled   is the bool representation of shuffleState
 * 
 * @return false if invalid shuffle state (i.e. not true/false), true otherwise
 */
bool checkShuffleState(string shuffleState, bool& isShuffled) {
  if (shuffleState == "true") {
    isShuffled = true;
  } else if (shuffleState == "false") {
    isShuffled = false;
  } else {
    // not "true" nor "false", so invalid
    cout << "invalid program usage: invalid first argument" << endl;
    return false;
  }
  return true; // valid otherwise
}

/**
 * Checks for the number of players.
 *
 * @param numPlayers is the cmd-line arg of number of players
 * @return false if invalid number of players (i.e. not 2-6 inclusive), true otherwise
 */
bool checkNumPlayers(int numPlayers) {
  // check for invalid number of players
  if (numPlayers < 2 || numPlayers > 6) {
    cout << "invalid program usage: num players must be 2-6" << endl;
    return false;
  }
  return true; // valid otherwise
}

/**
 * Checks for the stock size (based on number of players).
 *
 * @param numPlayers is the number of players that will determine stock size validity
 * @param stockSize  is the cmd-line arg for size of stock pile
 * @return false if invalid stock size, true otherwise
 */
bool checkStockSize(int numPlayers, int stockSize) {
  // if less than 6 players, stock size must be less than 30 cards
  if (numPlayers < 6) {
    if ((stockSize > 30) || (stockSize < 0)) {
      cout << "num players is " << numPlayers << endl;
      cout << "invalid program usage: bad stock size" << endl;
      return false;
    }
  }
  // if 6 players, stock size must be less than 20 cards
  else {
    if ((stockSize > 20) || (stockSize < 0)) {
      cout << "num players is " << numPlayers << endl;
      cout << "invalid program usage: bad stock size" << endl;
      return false;
    }
  }
  return true; // valid otherwise
}

/**
 * Checks for the file representing the deck.
 *
 * @param deckFile is the cmd-line arg for the string representing deck file
 * @return false if invalid deck file, true otherwise
 */
bool checkDeckFile(string deckFile) {
  // file name must be deck0.txt or deck1.txt
  ifstream checkfile(deckFile);
	   
  if (checkfile.fail()) {
    // cout << "invalid program usage: can't open deck file" << endl;
    return false;
  }
  return true; // valid otherwise
}

/**
 * Plays a game of Skip-Bo.
 *
 * @param newGame is the SkipBoGame object containing all the game info
 */
void playGame(SkipBoGame& newGame, bool& stopPlay) { 
  // loop through until the user wishes to save/quit
  bool continueGame = true;
  while (continueGame) {
    // print current player's turn and prompt action
    cout << " >> " << newGame.getCurPlayer() << " turn next" << endl;
    cout << "(p)lay, (s)ave, or (q)uit ? ";

    // store choice of user (i.e. 'p'/'s'/'q')
    char choice = '\0';
    cin >> choice;

    // user wants to play
    if (choice == 'p') {      
      newGame.makeMove(continueGame); // make move
      newGame.nextPlayer(); // move to next player
    }

    // user wants to save
    else if (choice == 's') {
      // save the game here
      string saveFile;
      cout << "save filename: ";
      cin >> saveFile;
      ofstream ofile(saveFile);

      //add the cards from the storedBuild piles to draw pile before saving
      newGame.addToDraw();
      
      ofile << newGame.toString();
      stopPlay = true;
      continueGame = false;
    }

    // user wants to quit
    else if (choice == 'q' || cin.eof()) {
      cout << "thanks for playing" << endl;
      stopPlay = true;
      continueGame = false;
    }

    // no valid commands
    else {
      cout << "illegal command, try again" << endl << endl;
    }
  }
}

/**
 * Controls the operations of the program.
 *
 * @return 1 if any error condition is reached, 0 otherwise
 */
int main(int argc, char **argv) {
  // check for valid number of arguments
  if (argc != 3 && argc != 5) {
    cout << "invalid program usage: invalid number of arguments" << endl;
    return 1;
  }

  // declare number of players, stock size, shuffled state deck file, and saved game file
  string shuffleState = argv[1];
  bool isShuffled = false;
  int numPlayers, stockSize;
  string savedGame, deckFile;

  // check for shuffle state
  if (!checkShuffleState(shuffleState, isShuffled)) return 1;

  /* check if loading in a saved game or starting a new one */  
  // if   argc == 3 -> loading save file
  // else argc == 5 -> creating a new game
  if (argc == 3) {
    savedGame = argv[2];
    // ensure game file is valid
    if (!checkDeckFile(savedGame)) {
      cout << "invalid program usage: can't open input game file" << endl; 
      return 1;
    }
    // create SkipBoGame object given the file input
    SkipBoGame loadedGame(savedGame,isShuffled);

    cout << endl;

    // begin playing the game
    bool stopPlay = false;
    playGame(loadedGame, stopPlay);

    // print winner once game has concluded
    if (!stopPlay) {
      loadedGame.getWinner();
    }
  } else {
    // check number of players
    numPlayers = atoi(argv[2]);
    if (!checkNumPlayers(numPlayers)) {
      return 1;
    }
    // check size of stock pile
    stockSize = atoi(argv[3]);
    if (!checkStockSize(numPlayers, stockSize)) {
      return 1;
    }
    // ensure deck file is valid
    deckFile = argv[4];
    if (!checkDeckFile(deckFile)) {
      cout << "num players is " << numPlayers << endl;
      cout << "stock size is " << stockSize << endl;
      cout << "invalid program usage: can't open deck file" << endl; 
      return 1;
    }
  
    // create a new game 
    SkipBoGame newGame(numPlayers, isShuffled, stockSize, deckFile);

    // print out number of players and stock size
    cout << "num players is " << numPlayers << endl;
    cout << "stock size is " << stockSize << endl;
    cout << endl;

    // begin playing the game
    bool stopPlay = false;
    playGame(newGame, stopPlay);
  }
  return 0;
}

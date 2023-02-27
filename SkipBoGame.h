#ifndef _SKIPBOGAME_H
#define _SKIPBOGAME_H

#include "Player.h"

#include <string>
#include <vector>
#include <istream>

/**
 * A Skip-Bo game.
 */
class SkipBoGame {
public:
  /**
   * Non-default constructor for SkipBoGame.
   * Creates a game.
   *
   * @param numPlayers is the number of Players in the game
   * @param isShuffled determines the shuffle state of the game
   * @param stockSize  is the size of the stock pile per Player
   * @param deckFile   is the name of the file containing the draw pile info
   */
  SkipBoGame(int numPlayers, bool isShuffled, int stockSize, std::string deckFile);

  /**
   * Non-default constructor for SkipBoGame.
   * Loads a game from a file.
   *
   * @param loadFile   is the name of the file containing the save data
   * @param isShuffled determines the shuffle state of the game
   */
  SkipBoGame(std::string loadFile, bool isShuffled);

  /**
   * Destructor for SkipBoGame.
   */
  ~SkipBoGame();

  /**
   * Gets the total number of Players.
   *
   * @return the number of Players.
   */
  int getNump() { return nump; }

  /**
   * Gets the size of the stock pile.
   *
   * @param return the stock size
   */
  int getSizeStock() { return sizeStock; }

  /**
   * Gets the name of the current Player.
   *
   * @return the name
   */
  std::string getCurPlayer() { return peep.at(curp).getName(); }

  /**
   * Gets the current Player's position.
   *
   * @return the position
   */
  int getCurpNum() { return curp; }

  /**
   * Gets the draw pile.
   *
   * @return the game's DrawPile
   */
  DrawPile getDraw() { return draw; }
  
  /**
   * Moves to the next Player.
   */
  void nextPlayer();

  /**
   * Add the stored build piles into the draw pile.
   */
  void addToDraw();
  
  /**
   * Determines the integer representation of the destination
   *
   * @param charDest is the destination of a Card
   * @return the integer representation of charDest
   */
  int determineDest(char charDest);
  
  /**
   * Parses user input for a move.
   *
   * @param act      is a reference to a char representing the action
   * @param charDest is a reference to a char representing the destination of a Card
   * @param orig     is a reference to an int representing the origin of a Card
   * @param dest     is a reference to an int representing the destination of a Card
   *
   * @return 0 if successfully moved, 1 otherwise
   */
  int getMove(char& act, char& charDest, int& orig, int& dest);

  /**
   * Executes a Player's move.
   *
   * @param continueGame is a reference to a bool representing whether the game will continue
   */
  void makeMove(bool& continueGame);

  /**
   * Determines the winner of the game.
   */
  void getWinner();
  
  /**
   * Converts SkipBoGame into a string representation.
   * 
   * @return the string SkipBoGame
   */
  std::string toString() const;

  /**
   * Reads in a SkipBoGame from an input stream (when loading a game).
   *
   * @param is is the input stream
   */
  void readIn(std::istream& is);
  
  /**
   * Displays SkipBoGame during gameplay.
   */
  void display() const;
  
protected:
  std::vector<Player> peep; // vector to store all players
  int nump; //total number of players
  DrawPile draw; // one draw pile for the entire game
  std::vector<FaceUpPile> build; // vector of 4 build piles
  int curp; // current player position w/in player vector
  int sizeStock; // stock pile size indicated by player/file
  std::vector<FaceUpPile> storedBuild; // vector of filled build piles
  
};

#endif

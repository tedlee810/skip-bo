#ifndef _PLAYER_H
#define _PLAYER_H

#include "FaceUpPile.h"
#include "DrawPile.h"
#include "Hand.h"

#include <vector>
#include <string>
#include <istream>

/**
 * A player.
 */
class Player {
public:

  /**
   * Non-default constructor for Player.
   * Creates a player with a specified name.
   *
   * @param playerName is the string representation of the name
   */
  Player(std::string playerName);

  /**
   * Destructor for Player.
   */
  ~Player();

  /**
   * Returns the name of the Player.
   *
   * @return the name
   */
  std::string getName() const { return name; }
  
  /**
   * Adds a Card to the Player's stock pile.
   *
   * @param c is the Card to add
   */
  void addToStock(Card c) { stock.addCard(c); }

  /**
   * Adds a Card to the Player's Hand.
   *
   * @param c is the Card to add
   */
  void addToHand(Card c) { hand.addCard(c); }

  /**
   * Moves a Card from the Player's stock pile.
   *
   * @param dest  is the destination of the Card to move
   * @param build is a reference to the build pile
   *
   * @return 1 if sucessfully moved, 0 otherwise
   */
  int stockMove(int dest, std::vector<FaceUpPile>& build);

  /**
   * Moves a Card from the Player's discard pile.
   *
   * @param orig  is the original position of the Card (i.e. which discard pile)
   * @param dest  is the destination of the Card to move
   * @param build is a reference to the build pile
   *
   * @return 1 if successfully moved, 0 otherwise
   */
  int discardMove(int orig, int dest, std::vector<FaceUpPile>& build);

  /**
   * Moves a Card from the Player's Hand.
   *
   * @param orig  is the original position of the Card (i.e. which Hand position)
   * @param dest  is the destination of the Card to move
   * @param build is a reference object to the build pile
   *
   * @return 1 if successfully moved to a build pile
   *         2 if successfully moved to a discard pile
   *         0 otherwise
   */
  int handMove(int orig, int dest, std::vector<FaceUpPile>& build);

  /**
   * Converts Player into a string representation.
   *
   * @return the string Player
   */
  std::string toString() const;
  
  /**
   * Reads in a Player from an input stream (when loading a game).
   *
   * @param is is the input stream
   */
  void readIn(std::istream& is);
  
  /**
   * Displays Player during gameplay.
   */ 
  void display() const;

protected:
  friend class SkipBoGame; // SkipBoGame has access to Player fields
  std::string name; // Player's name
  FaceUpPile stock; // Player's stock pile
  std::vector<FaceUpPile> discard; // Player's discard pile
  Hand hand; // Player's hand
};

#endif

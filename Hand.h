#ifndef _HAND_H
#define _HAND_H

#include "DrawPile.h"

#include <vector>
#include <string>

/**
 * The player's hand.
 */
class Hand {
public:

  /**
   * Destructor for Hand.
   */
  ~Hand();

  /**
   * Gets the Card value of a given position.
   *
   * @param pos is the integer representation of the position of the Card
   * @return the value of the Card
   */
  int getCard(int pos) { return hand[pos].getValue(); }

  /**
   * Gets the size of the Hand.
   *
   * @return the size of the Hand
   */
  int size() const { return hand.size(); }

  /**
   * Removes a card at a given position and returns it.
   *
   * @param pos is the integer representation of the position of the Card
   * @return the Card that was removed
   */
  Card popCard(int pos);

  /**
   * Adds a Card to the Hand.
   */
  virtual void addCard(const Card& c) { hand.push_back(c); }

  /**
   * Replenishes the hand.
   *
   * @param draw is a reference to the main DrawPile of the game
   */
  void replenish(DrawPile& draw);

  /**
   * Converts Hand into a string representation.
   *
   * @return the string Hand
   */
  std::string toString() const;
  
  /**
   * Displays Hand during gameplay.
   */
  void display() const;

private:
  std::vector<Card> hand; // a vector of Cards representing the Hand
};

#endif

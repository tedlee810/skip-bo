#ifndef _PILE_H
#define _PILE_H

#include "Card.h"

#include <fstream>
#include <string>
#include <vector>

/**
 * A pile of Skip-Bo cards (e.g. a draw pile or build pile).
 */
class Pile {
public:

  /**
   * Default constructor for Pile.
   */
  Pile() { }

  /**
   * Copy constructor for Pile.
   * 
   * @param rhs is a constant reference to the input Pile object
   */
  Pile(const Pile& rhs);

  /**
   * Destructor for Pile.
   */
  virtual ~Pile();
  
  /**
   * Assignment operator for Pile.
   *
   * @param rhs is a constant reference to the input Pile object
   * @return the new Pile
   */
  Pile& operator=(const Pile& rhs);

  /**
   * Returns the size of the Pile.
   *
   * @return the size
   */
  int size() const { return pile.size(); }

  /**
   * Adds a Card to the Pile.
   *
   * @param c is a constant reference to the input Card object to be added
   */
  void addCard(const Card& c) { pile.push_back(c); }

  /**
   * Adds a Pile passed in to the this Pile.
   *
   * @param clearPile is a constant reference to the input Pile object to be added
   */
  void addPile(Pile& clearPile);

  /**
   * Removes the top Card and returns it.
   *
   * @return the removed Card
   */
  Card popCard();

  /**
   * Clears the Pile.
   */
  void clear() { pile.clear(); }
  
  /**
   * Converts Pile into a string representation.
   *
   * @return the string Pile
   */
  std::string toString() const; 

  /**
   * Reads in a Pile from an input stream (when loading a game).
   *
   * @param is is the input stream
   */
  void readIn(std::istream& is);

  /**
   * Displays Pile during gameplay.
   */
  virtual void display() const = 0;
  
protected:
  std::vector<Card> pile; // a vector of Cards representing the Pile
};

#endif

#ifndef _CARD_H
#define _CARD_H

#include <string>

/**
 * A Skip-Bo playing card.
 */
class Card {
public:
  
  /**
   * Default constructor for Card.
   * Sets value to 0.
   */
  Card() : value(0) { }

  /**
   * Non-default constructor for Card.
   * Sets value based on given parameter between to 0 and 12 (0 otherwise).
   *
   * @param v is the value of a Skip-Bo card to create
   */
  Card(int v) { value = v >= 0 && v <= 12 ? v : 0; }

  /**
   * Copy constructor for Card.
   *
   * @param rhs is a constant reference to the input Card object
   */
  Card(const Card& rhs);

  /**
   * Destructor for Card.
   */
  ~Card() { }

  /**
   * Assignment operator for Card.
   *
   * @param rhs is a constant reference to the input Card object
   */
  void operator=(const Card& rhs);

  /**
   * Returns the value of Card.
   */
  int getValue() const { return value; }

  /**
   * Converts Card into a string representation.
   *
   * @return the string Card
   */
  std::string toString() const; 

  /**
   * Displays Card during gameplay.
   */
  void display() const;  
  
protected:
  int value; // value of the Card
};

#endif

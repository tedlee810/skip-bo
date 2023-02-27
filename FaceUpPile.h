#ifndef _FACEUPPILE_H
#define _FACEUPPILE_H

#include "Pile.h"

/**
 * A face-up pile of Skip-Bo cards.
 */
class FaceUpPile : public Pile {
public:

  /**
   * Default constructor for FaceUpPile.
   */
  FaceUpPile() { }

  /**
   * Copy constructor for FaceUpPile.
   *
   * @param rhs is a constant reference to the input FaceUpPile object
   */
  FaceUpPile(const FaceUpPile& rhs);

  /**
   * Returns the value of the top card.
   *
   * @return the integer value of the card
   */
  int getTopCard();

  /**
   * Displays FaceUpPile during gameplay.
   */
  void display() const override;
};

#endif

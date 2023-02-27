#ifndef _DRAWPILE_H
#define _DRAWPILE_H

#include "Pile.h"

#include <string>

/** 
 * A draw pile of Skip-Bo card.
 */
class DrawPile : public Pile { 
public:

  /**
   * Non-default constructor for DrawPile.
   * Creates a DrawPile object (inherited from Pile).
   *
   * @param shuffle determines whether DrawPile is shuffled
   */
  DrawPile(bool shuffle) : isShuffled(shuffle) { }
  
  /**
   * Non-default constructor for DrawPile.
   * Creates a DrawPile object (inherited from Pile) with data from a txt file.
   *
   * @param shuffle  determines whether DrawPile is shuffled
   * @param filename is the name of file to read from
   */
  DrawPile(bool shuffle, std::string filename);

  /**
   * Shuffles DrawPile if shuffling is enabled.
   *
   * @param shuffle determines whether DrawPile is shuffled
   */
  void helpShuffle(bool shuffle);

  /**
   * Returns a string representation of the shuffle state of DrawPile.
   */
  std::string getRand() const;

  /**
   * Destructor for DrawPile.
   */
  ~DrawPile() { }

  /**
   * Display contents of DrawPile during game play.
   */
  void display() const override;

private:
  bool isShuffled; // the shuffle state of the DrawPile
};

#endif

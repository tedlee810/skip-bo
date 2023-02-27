# Sarah Lee  - tlee144
# Ted Lee    - slee470
# Amy Mistri - amistri1

CC = g++
CONSERVATIVE_FLAGS = -std=c++11 -Wall -Wextra -pedantic
DEBUGGING_FLAGS = -g -O0
CFLAGS = $(CONSERVATIVE_FLAGS) $(DEBUGGING_FLAGS)

skipbo: main.cpp SkipBoGame.h SkipBoGame.o Player.o Card.o Hand.o Pile.o FaceUpPile.o DrawPile.o
	$(CC) $(CFLAGS) -o skipbo main.cpp SkipBoGame.o Player.o Card.o Hand.o Pile.o FaceUpPile.o DrawPile.o

SkipBoGame.o: SkipBoGame.cpp SkipBoGame.h
	$(CC) $(CFLAGS) -c SkipBoGame.cpp

Player.o: Player.cpp Player.h
	$(CC) $(CFLAGS) -c Player.cpp

Card.o: Card.cpp Card.h
	$(CC) $(CLAGS) -c Card.cpp

Hand.o: Hand.cpp Hand.h
	$(CC) $(CFLAGS) -c Hand.cpp

Pile.o: Pile.cpp Pile.h
	$(CC) $(CFLAGS) -c Pile.cpp

FaceUpPile.o: FaceUpPile.cpp FaceUpPile.h
	$(CC) $(CFLAGS) -c FaceUpPile.cpp

DrawPile.o: DrawPile.cpp DrawPile.h
	$(CC) $(CFLAGS) -c DrawPile.cpp

clean:
	rm -f *.o skipbo

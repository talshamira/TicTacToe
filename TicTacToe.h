#ifndef TICTACTOE_H
#define TICTACTOE_H
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#define M 3
#define ERROR1 "Error getting the name inputed goodbye\n"
#define ERROR2 "Error getting the character inputed goodbye\n"
#define BUFFER_Size 256
#define ERROR3 "Empty String\n"
#define PLAYER1 1
#define PLAYER2 2
#define PRINT 10

typedef enum ERROR {DATA_FAIL, EMPTY_STRING, SUCCESS} ERROR;

typedef enum Winner {FIRSTPLAYER, SECONDPLAYER, TIE, NOWINNER} Winner;
typedef enum Character {X, O} Character; 
typedef struct {
   Character character;
   char *name; 
} Player;

typedef struct {
    Player player1;
    Player player2;
    Character board[M][M];
    int turn;
    Winner winner;
} Game;

ERROR getParamaters(Game *game);
void printBoard(const Game *game);
ERROR getChar(char *choice);
bool checkDown(const Game *game, const char choice, const Character playerCharacter);
bool checkLeft(const Game *game, const char choice, const Character playerCharacter);
void whoIsWinner(Game *game);
bool checkPrimaryDiaganal(const Game *game, const Character playerCahracter);
bool checkSecondaryDiaganal(const Game *game, const Character playerCahracter);
bool isFull(const Game *game);
void getWinner(Game *game ,const int choice);
ERROR turn(Game *game);
bool isValidChoice(const Game *game, const int choice);
void enterChoice(Game *game, const int choice, const Character playerCharacter);
#endif
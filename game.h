#ifndef GAME_H
#define GAME_H

#include <stdbool.h> 


typedef struct {
    int rows;           
    int cols;           
    char **board;       
    char p1_sym;        
    char p2_sym;        
    int current_player; 
} GameState;


void initGame(GameState *game, int r, int c, char sym1, char sym2);
void freeGame(GameState *game);
void printBoard(GameState *game);
bool makeMove(GameState *game, int r, int c);
bool checkWin(GameState *game);
bool isBoardFull(GameState *game);

#endif
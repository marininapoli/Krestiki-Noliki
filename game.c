#include <stdio.h>
#include <stdlib.h>
#include "game.h"


void initGame(GameState *game, int r, int c, char sym1, char sym2) {
    game->rows = r;
    game->cols = c;
    game->p1_sym = sym1;
    game->p2_sym = sym2;
    game->current_player = 1;

    
    game->board = (char **)malloc((size_t)r * sizeof(char *));
    for (int i = 0; i < r; i++) {
        
        game->board[i] = (char *)malloc((size_t)c * sizeof(char));
        for (int j = 0; j < c; j++) {
            game->board[i][j] = ' '; 
        }
    }
}


void freeGame(GameState *game) {
    for (int i = 0; i < game->rows; i++) {
        free(game->board[i]);
    }
    free(game->board);
}


void printBoard(GameState *game) {
    printf("\n   ");
    for (int j = 0; j < game->cols; j++) printf("%d   ", j); 
    printf("\n");

    for (int i = 0; i < game->rows; i++) {
        printf("  ");
        for (int j = 0; j < game->cols; j++) printf("+---");
        printf("+\n");
        
        printf("%d ", i); 
        for (int j = 0; j < game->cols; j++) {
            printf("| %c ", game->board[i][j]);
        }
        printf("|\n");
    }
    printf("  ");
    for (int j = 0; j < game->cols; j++) printf("+---");
    printf("+\n\n");
}


bool makeMove(GameState *game, int r, int c) {
    
    if (r < 0 || r >= game->rows || c < 0 || c >= game->cols) {
        printf("Ошибка: такой клетки не существует!\n");
        return false;
    }
    
    if (game->board[r][c] != ' ') {
        printf("Ошибка: эта клетка уже занята!\n");
        return false;
    }

    
    char sym = (game->current_player == 1) ? game->p1_sym : game->p2_sym;
    game->board[r][c] = sym;
    return true;
}


bool checkWin(GameState *game) {
    
    for (int i = 0; i < game->rows; i++) {
        char first = game->board[i][0];
        if (first == ' ') continue; 
        bool win = true;
        for (int j = 1; j < game->cols; j++) {
            if (game->board[i][j] != first) { win = false; break; }
        }
        if (win) return true;
    }

    
    for (int j = 0; j < game->cols; j++) {
        char first = game->board[0][j];
        if (first == ' ') continue;
        bool win = true;
        for (int i = 1; i < game->rows; i++) {
            if (game->board[i][j] != first) { win = false; break; }
        }
        if (win) return true;
    }

    
    if (game->rows == game->cols) {
        char first = game->board[0][0];
        if (first != ' ') {
            bool win = true;
            for (int i = 1; i < game->rows; i++) {
                if (game->board[i][i] != first) { win = false; break; }
            }
            if (win) return true;
        }

        
        first = game->board[0][game->cols - 1];
        if (first != ' ') {
            bool win = true;
            for (int i = 1; i < game->rows; i++) {
                if (game->board[i][game->cols - 1 - i] != first) { win = false; break; }
            }
            if (win) return true;
        }
    }
    return false;
}


bool isBoardFull(GameState *game) {
    for (int i = 0; i < game->rows; i++) {
        for (int j = 0; j < game->cols; j++) {
            if (game->board[i][j] == ' ') return false; 
        }
    }
    return true;
}
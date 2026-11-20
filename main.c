#include <stdio.h>
#include "game.h"

int main(void) {
    GameState game;
    int r, c;
    char sym1, sym2;

    printf("=== ДОБРО ПОЖАЛОВАТЬ В КРЕСТИКИ-НОЛИКИ ===\n");

    
    do {
        printf("Введите количество строк (N > 1): ");
        scanf("%d", &r);
    } while (r <= 1);

    do {
        printf("Введите количество столбцов (M > 1): ");
        scanf("%d", &c);
    } while (c <= 1);

    
    printf("Игрок 1, выберите ваш символ (например, X): ");
    scanf(" %c", &sym1);
    
    do {
        printf("Игрок 2, выберите ваш символ (не совпадающий с первым): ");
        scanf(" %c", &sym2);
    } while (sym2 == sym1);

    
    initGame(&game, r, c, sym1, sym2);

    int row_move, col_move;

    
    while (1) {
        printBoard(&game); 

        printf("Ход игрока %d (%c).\n", game.current_player, 
               game.current_player == 1 ? game.p1_sym : game.p2_sym);

        printf("Введите строку и столбец (через пробел): ");
        scanf("%d %d", &row_move, &col_move);

        
        if (!makeMove(&game, row_move, col_move)) {
            continue; 
        }

        
        if (checkWin(&game)) {
            printBoard(&game);
            printf("🎉 ПОБЕДИЛ ИГРОК %d (%c)! 🎉\n", game.current_player, 
                   game.current_player == 1 ? game.p1_sym : game.p2_sym);
            break;
        } else if (isBoardFull(&game)) {
            printBoard(&game);
            printf("🤝 НИЧЬЯ! Поле заполнено. 🤝\n");
            break;
        }

        
        game.current_player = (game.current_player == 1) ? 2 : 1;
    }

    
    freeGame(&game);

    return 0;
}
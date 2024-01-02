#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include "sudoku.h"

char posnums[10] = {0};
long solution_number = 0;
int solution_depth = 0;

extern int valid_sudoku(sudoku *s);

int load_sudoku(char *filename, sudoku *s)
{
    FILE *inp;
    int row, col;
    int c;
    
    inp = fopen(filename, "r");
    if (inp == NULL) return 0;

    /* Clear the playfield */
    for (row = 0; row < SUDOKU_SIZE; row++)
        for (col = 0; col < SUDOKU_SIZE; col++)
            s->playfield[row][col] = '-';
    
    row = 0;
    col = 0;
    
    do {
        c = fgetc(inp);
        /*Kontrola, jestli je v souboru -, 1-9*/
        if (c == '-' || (c >= '1' && c <= '9')) {
            s->playfield[row][col] = (char) c; /*Nastaví dvou rozměrné pole na znaky přčtené ze souboru*/
            col++;
            
            if (col >= SUDOKU_SIZE) { /*Pokud dojede nakonec řádku, skočí na další řádek*/
                col = 0;
                row++;
            }
        }
        
    } while (c != EOF);

    
    fclose(inp);
    
    return 1;
}

void print_sudoku(sudoku *s)
{
    int i, j;
    
    printf("|-------+-------+-------|\n");

    for (i = 0; i < SUDOKU_SIZE; i++) {
        printf("| ");
        for (j = 0; j < SUDOKU_SIZE; j++) {
            printf("%c ", s->playfield[i][j]);
            if (!((j + 1) % 3)) printf("| ");
        }
        
        if (!((i + 1) % 3)) printf("\n|-------+-------+-------|\n");
        else printf("\n");
    }
}

void get_possibilities(sudoku *s, int i, int j, char *pos)
{
    memset(pos, 0, 10);
    strcpy(pos, "123456789");
}

int solve_sudoku(sudoku *s, int depth)
{
    int i, j, k;
    int found = 0;
    int valck = 0;
    
    printf("\x0D%d", depth);
    
    valck = valid_sudoku(s);
    if (!valck) return 0;
    
    for (i = 0; i < SUDOKU_SIZE; i++) {
        for (j = 0; j < SUDOKU_SIZE; j++)
            if (s->playfield[i][j] == '-') {
                found = 1;
                break;
            }
        if (found) break;
    }
    
    if (!found && valck) {
        printf("\n");
        print_sudoku(s);
        return 1;
    }
            
    get_possibilities(s, i, j, posnums);
    
    for (k = 0; k < strlen(posnums); k++) {
        s->playfield[i][j] = posnums[k];
        if (!solve_sudoku(s, depth + 1)) s->playfield[i][j] = '-';
    }
    
    return 0;
}

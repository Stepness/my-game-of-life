#include <stdio.h>

#define GRID_COLS 70
#define GRID_ROWS 25
#define ALIVE '1'
#define DEAD '0'

int main(void) {
    puts("\x1b[2J");
    char grid[GRID_COLS*GRID_ROWS];
    
    for(int i = 0; i < sizeof(grid); i++) {
        grid[i] = DEAD;
    }

    for(int i = 0; i < GRID_ROWS; i++) {
        char str[GRID_COLS+1];
        for(int j = 0; j < GRID_COLS; j++){
            str[j] = grid[i*(GRID_COLS)+j];
        }
        str[GRID_COLS] = '\0';
        printf("%s\n", str);
    }

    return 0;
}
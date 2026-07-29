#include <stdio.h>
#include <unistd.h>

#define GRID_COLS 3
#define GRID_ROWS 3
#define ALIVE '1'
#define DEAD '0'

char getCell(char grid[], int x, int y) {
    return grid[y*(GRID_COLS)+x];
}

void setCell(char* grid, int x, int y, char val) {
    grid[y*(GRID_COLS)+x] = val;
}

void printGrid(char grid[]) {
    for(int i = 0; i < GRID_ROWS; i++) {
        char str[GRID_COLS+1];
        for(int j = 0; j < GRID_COLS; j++){
            str[j] = grid[i*(GRID_COLS)+j];
        }
        str[GRID_COLS] = '\0';
        printf("%s\n", str);
    }
}

void initGrid(char* grid, int size) {
    for(int i = 0; i < size; i++) {
        grid[i] = DEAD;
    }
}

void newGeneration(char* grid) {}

int main(void) {
    puts("\x1b[2J");
    char grid[GRID_COLS*GRID_ROWS];
    int gridSize = sizeof(grid);

    initGrid(grid, gridSize);

    setCell(grid, 1, 1, ALIVE);
    setCell(grid, 1, 2, ALIVE);
    setCell(grid, 1, 0, ALIVE);

    while(1){
        puts("\x1b[2J");

        newGeneration(grid);
        printGrid(grid);

        sleep(1);
    }

    return 0;
}
#include <stdio.h>
#include <unistd.h>

#define GRID_COLS 50
#define GRID_ROWS 30
#define ALIVE '*'
#define DEAD '.'

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

void initDeadGrid(char* grid, int size) {
    for(int i = 0; i < size; i++) {
        grid[i] = DEAD;
    }
}

int getAliveNeighbours(char* grid, int x, int y) {

    int quantity = 0;

    if (x > 0 && y > 0) { 
        if (getCell(grid, x-1, y-1) == ALIVE) quantity++; // TOPLEFT
    } 

    if (y > 0) {
        if (getCell(grid, x, y-1) == ALIVE) quantity++; // TOPCENTER
    }

    if (x < GRID_COLS-1 && y > 0) {
        if (getCell(grid, x+1, y-1) == ALIVE) quantity++; // TOPRIGHT
    }

    if (x > 0) {
        if (getCell(grid, x-1, y) == ALIVE) quantity++; // LEFT
    }

    if (x < GRID_COLS-1) {
        if (getCell(grid, x+1, y) == ALIVE) quantity++; // RIGHT
    }

    if (x > 0 && y < GRID_ROWS-1) {
        if (getCell(grid, x-1, y+1) == ALIVE) quantity++; // BOTTOMLEFT
    }

    if (y < GRID_ROWS-1) {
        if (getCell(grid, x, y+1) == ALIVE) quantity++; // BOTTOM
    }

    if (x < GRID_COLS-1 && y < GRID_ROWS-1) {
        if (getCell(grid, x+1, y+1) == ALIVE) quantity++; // BOTTOMRIGHT
    }

    //printf("Neighbours of (%d, %d): %d\n", x, y, quantity);
    
    return quantity;
}

void newGeneration(char* grid, char* newGrid) {
    
    for(int i = 0; i < GRID_ROWS; i++) {
        for(int j = 0; j < GRID_COLS; j++){
            int aliveNeigbours = getAliveNeighbours(grid, j, i);
            int currentCellIndex = i*(GRID_COLS)+j;
            if (getCell(grid, j, i) == ALIVE) {
                switch (aliveNeigbours)
                {
                    case  0 ... 1:
                        newGrid[currentCellIndex] = DEAD;
                        break;
                    case  2 ... 3:
                        newGrid[currentCellIndex] = ALIVE;
                        break;
                    case 4 ... 8:
                        newGrid[currentCellIndex] = DEAD;
                        break;
                }
            } else if (aliveNeigbours == 3) {
                newGrid[currentCellIndex] = ALIVE;
            } else {
                newGrid[currentCellIndex] = DEAD;
            }
            
        }
    }
}

void initPlusGrid(char* grid) {
    // Grid that becomes a +
    setCell(grid, 1, 1, ALIVE);
    setCell(grid, 1, 2, ALIVE);
    setCell(grid, 1, 0, ALIVE);
}

void initGliderGunGrid(char* grid) {
    setCell(grid, 1, 0, ALIVE);
    setCell(grid, 2, 1, ALIVE);
    setCell(grid, 0, 2, ALIVE);
    setCell(grid, 1, 2, ALIVE);
    setCell(grid, 2, 2, ALIVE);
    setCell(grid, 6, 1, ALIVE);
    setCell(grid, 7, 1, ALIVE);
    setCell(grid, 8, 1, ALIVE);
    setCell(grid, 6, 2, ALIVE);
    setCell(grid, 8, 2, ALIVE);
    setCell(grid, 6, 3, ALIVE);
    setCell(grid, 7, 3, ALIVE);
    setCell(grid, 8, 3, ALIVE);
}

void initGosperGliderGunGrid(char* grid) {
    setCell(grid, 1, 5, ALIVE);
    setCell(grid, 1, 6, ALIVE);
    setCell(grid, 2, 5, ALIVE);
    setCell(grid, 2, 6, ALIVE);

    setCell(grid, 11, 5, ALIVE);
    setCell(grid, 11, 6, ALIVE);
    setCell(grid, 11, 7, ALIVE);

    setCell(grid, 12, 4, ALIVE);
    setCell(grid, 12, 8, ALIVE);

    setCell(grid, 13, 3, ALIVE);
    setCell(grid, 13, 9, ALIVE);

    setCell(grid, 14, 3, ALIVE);
    setCell(grid, 14, 9, ALIVE);

    setCell(grid, 15, 6, ALIVE);

    setCell(grid, 16, 4, ALIVE);
    setCell(grid, 16, 8, ALIVE);

    setCell(grid, 17, 5, ALIVE);
    setCell(grid, 17, 6, ALIVE);
    setCell(grid, 17, 7, ALIVE);

    setCell(grid, 18, 6, ALIVE);

    setCell(grid, 21, 3, ALIVE);
    setCell(grid, 21, 4, ALIVE);
    setCell(grid, 21, 5, ALIVE);

    setCell(grid, 22, 3, ALIVE);
    setCell(grid, 22, 4, ALIVE);
    setCell(grid, 22, 5, ALIVE);

    setCell(grid, 23, 2, ALIVE);
    setCell(grid, 23, 6, ALIVE);

    setCell(grid, 25, 1, ALIVE);
    setCell(grid, 25, 2, ALIVE);
    setCell(grid, 25, 6, ALIVE);
    setCell(grid, 25, 7, ALIVE);

    setCell(grid, 35, 3, ALIVE);
    setCell(grid, 35, 4, ALIVE);

    setCell(grid, 36, 3, ALIVE);
    setCell(grid, 36, 4, ALIVE);
}


int main(void) {
    puts("\x1b[2J");
    char grid[GRID_COLS*GRID_ROWS];
    int gridSize = sizeof(grid);
    char newGrid[GRID_COLS*GRID_ROWS];

    initDeadGrid(grid, gridSize);

    // initPlusGrid(grid);
    // initGliderGunGrid(grid);
    initGosperGliderGunGrid(grid);
    printGrid(grid);

    char *current = grid;
    char *next = newGrid;
    while(1){
        puts("\x1b[2J");
        newGeneration(current, next);
        printGrid(next);
        char *temp = current;
        current = next;
        next = temp;
        
        usleep(250*1000); // Microseconds
    }

    return 0;
}
/*
 * img/maze.c
 *
 * Rectangular maze generation
 */

#include "maze.h"
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <time.h>

// Generate a maze using randomized depth-first
// * Start with a random cell
// * Select random unvisited neighbor
// * Link cells, mark new as visited
// * Add to stack and repeat with new node
// * When dead end, backtrack up stack

typedef enum dir { Up, Down, Left, Right } Direction;

// Contain node information, including visited flag and connected neighbors
typedef struct cell {
    int nCell;
    // TODO: Switch to flags in single byte if this takes up too much space
    bool visited;
    bool up;
    bool down;
    bool left;
    bool right;
} Cell;

// Get an adjacent cell index, or -1 if none exist
int getNeighborCell(int nCell, int width, int height, Direction dir)
{
    if (width < 1 || height < 1 || nCell < 0 || nCell >= width*height) {
        return -1;
    }

    switch(dir) {
        case Left:
            return ((nCell % width) == 0) ? -1 : nCell - 1;
        case Right:
            return ((nCell % width) == (width - 1)) ? -1 : nCell + 1;
        case Up:
            return (nCell < width) ? -1 : nCell - width;
        case Down:
            return (nCell > (width * (height - 1))) ? -1 : nCell + width;
        default:
            return -1;
    }
}

Cell * genMaze(int width, int height)
{
    if (width < 1 || height < 1) {
        fprintf(stderr, "Dimensions must be positive integers\n");
        return NULL;
    }

    int nCells = width * height;

    Cell * pMaze = malloc(nCells * sizeof(Cell));
    if (pMaze == NULL) {
        fprintf(stderr, "Failed to allocate memory for maze\n");
        return NULL;
    }

    int * pStack = malloc(nCells * sizeof(int));
    if (pStack == NULL) {
        fprintf(stderr, "Failed to allocate memory for stack\n");
        if (pMaze != NULL) free(pMaze);
        return NULL;
    }
    
    srand(time(NULL));

    int nStart = rand() % nCells;

    Cell * startCell = &pMaze[nStart];
    Cell * curCell = startCell;

    while(1) {
        curCell->visited = true;

        int up    = getNeighborCell(curCell->nCell, width, height, Up);
        int down  = getNeighborCell(curCell->nCell, width, height, Down);
        int left  = getNeighborCell(curCell->nCell, width, height, Left);
        int right = getNeighborCell(curCell->nCell, width, height, Right);

        bool upOk    = (up    != -1 && !pMaze[up].visited);
        bool downOk  = (down  != -1 && !pMaze[down].visited);
        bool leftOk  = (left  != -1 && !pMaze[left].visited);
        bool rightOk = (right != -1 && !pMaze[right].visited);
    }

    return NULL;
}

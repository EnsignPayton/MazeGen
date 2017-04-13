/*
 * img/maze.c
 *
 * Rectangular maze generation
 */

#include "maze.h"
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

typedef enum dir { Up, Down, Left, Right } Direction;

/*
 * Static (Private) Functions
 */

// Get an adjacent cell index, or -1 if none exist
static int getNeighborCell(int nCell, int width, int height, Direction dir)
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

// Get a random direction from available directions
//-1 = NONE
// 0 = UP
// 1 = DOWN
// 2 = LEFT
// 3 = RIGHT
static int getRandDir(bool up, bool down, bool left, bool right)
{
    int n = -1;
    int r;

    // One available
    if (up && !down && !left && !right)
        n = 0;
    if (!up && down && !left && !right)
        n = 1;
    if (!up && !down && left && !right)
        n = 2;
    if (!up && !down == !left && right)
        n = 3;

    // Two available
    if (up && down && !left && !right)
        n = rand() % 2;
    if (up && !down && left && !right)
        n = rand() % 2 ? 0 : 2;
    if (up && !down && !left && right)
        n = rand() % 2 ? 0 : 3;
    if (!up && down && left && !right)
        n = rand() % 2 ? 1 : 2;
    if (!up && down && !left && right)
        n = rand() % 2 ? 1 : 3;
    if (!up && !down && left && right)
        n = rand() % 2 ? 2 : 3;

    // Three available
    if (up && down && left && !right) {
        n = rand() % 3;
    }
    if (up && down && !left && right) {
        r = rand() % 3;
        n = r == 2 ? 3 : r;
    }
    if (up && !down && left && right) {
        r = (rand() % 3) + 1;
        n = r == 1 ? 0 : r;
    }
    if (!up && down && left && right) {
        n = (rand() % 3) + 1;
    }

    // Four available
    if (up && down && left && right)
        n = rand() % 4;

    return n;
}

/*
 * Public Functions
 */

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

    for (int i = 0; i < nCells; i++) {
        pMaze[i].nCell = i;
        pMaze[i].visited = false;
        pMaze[i].up = false;
        pMaze[i].down = false;
        pMaze[i].left = false;
        pMaze[i].right = false;
    }

    int nStart = rand() % nCells;
    int nStack = 0;

    Cell * startCell = &pMaze[nStart];
    Cell * curCell = startCell;

    bool done = false;
    while(!done) {
        curCell->visited = true;

        int up    = getNeighborCell(curCell->nCell, width, height, Up);
        int down  = getNeighborCell(curCell->nCell, width, height, Down);
        int left  = getNeighborCell(curCell->nCell, width, height, Left);
        int right = getNeighborCell(curCell->nCell, width, height, Right);

        bool upOk    = (up    != -1 && !pMaze[up].visited);
        bool downOk  = (down  != -1 && !pMaze[down].visited);
        bool leftOk  = (left  != -1 && !pMaze[left].visited);
        bool rightOk = (right != -1 && !pMaze[right].visited);

        int next = getRandDir(upOk, downOk, leftOk, rightOk);
        if (next == 0) {
            next = up;
            curCell->up = true;
            pMaze[next].down = true;
        }
        if (next == 1) {
            next = down;
            curCell->down = true;
            pMaze[next].up = true;
        }
        if (next == 2) {
            next = left;
            curCell->left = true;
            pMaze[next].right = true;
        }
        if (next == 3) {
            next = right;
            curCell->right = true;
            pMaze[next].left = true;
        }

        if (next != -1) {
            pStack[nStack] = next;
            nStack += 1;
            curCell = &pMaze[next];
        } else if (nStack != 0) {
            curCell = &pMaze[pStack[nStack - 1]];
            nStack -= 1;
        } else {
            done = true;
            ;
        }
    }

    if (pStack != NULL) free(pStack);

    return pMaze;
}

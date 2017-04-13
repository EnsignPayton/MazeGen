#ifndef MAZE_H
#define MAZE_H

/*
 * img/maze.h
 *
 * Rectangular maze generation
 */

#include <stdbool.h>

// Represents a cell of a maze
typedef struct cell {
    // Index of cell, from 0 to (width * height) - 1
    int nCell;
    // Cell visited flag. Used for constructing the maze.
    bool visited;
    // Connected to upper adjacent cell
    bool up;
    // Connected to lower adjacent cell
    bool down;
    // Connected to left adjacent cell
    bool left;
    // Connected to right adjacent cell
    bool right;
} Cell;

// Returns a maze of size (width * height) generated using
// randomized depth-first.
Cell * genMaze(int width, int height);

#endif

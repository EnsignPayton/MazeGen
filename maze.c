/*
 * img/maze.c
 *
 * Rectangular maze generation
 */

#include "maze.h"

// Generate a maze using randomized depth-first
// * Start with a random cell
// * Select random unvisited neighbor
// * Link cells, mark new as visited
// * Add to stack and repeat with new node
// * When dead end, backtrack up stack

// Contain ... pick this back up
typedef struct cell {
    int nCell;
    // TODO: Switch to flags in single byte if this takes up too much space
    bool visited;
    bool up;
    bool down;
    bool left;
    bool right;
} Cell;

/*
 * img/main.c
 *
 * Entry point for image manipulation software
 */

#include "mypng.h"
#include "maze.h"

#include <stdio.h>
#include <stdlib.h>
#include <time.h>

RGB * genTestImg(int width, int height)
{
    RGB * pixels = malloc(width * height * sizeof(RGB));
    if (pixels == NULL) {
        fprintf(stderr, "Failed to allocate pixel array\n");
        return NULL;
    }

    for (int x = 0; x < width; x++) {
        for (int y = 0; y < height; y++) {
            int color = rand() % 2 ? 0 : 255;
            pixels[y*width + x].red = color;
            pixels[y*width + x].green = color;
            pixels[y*width + x].blue = color;
        }
    }

    return pixels;
}

RGB * genMazeImg(Cell * pMaze, int width, int height)
{
    if (pMaze == NULL || width < 1 || height < 1) {
        fprintf(stderr, "Invalid parameters\n");
        return NULL;
    }

    int imgWidth = (width * 2) + 1;
    int imgHeight = (height * 2) + 1;

    RGB * pixels = malloc(imgWidth * imgHeight * sizeof(RGB));
    if (pixels == NULL) {
        fprintf(stderr, "Failed to allocate pixel array\n");
        return NULL;
    }

    // Black fill (creates border)
    int x, y;
    for (x = 0; x < imgWidth; x++) {
        for (y = 0; y < imgHeight; y++) {
            pixels[y*imgWidth + x].red = 0;
            pixels[y*imgWidth + x].green = 0;
            pixels[y*imgWidth + x].blue = 0;
        }
    }

    // Maze cells
    for (x = 0; x < width; x++) {
        for (y = 0; y < height; y++) {
            pixels[(y*2 + 1)*imgWidth + (x*2 + 1)].red = 255;
            pixels[(y*2 + 1)*imgWidth + (x*2 + 1)].green = 255;
            pixels[(y*2 + 1)*imgWidth + (x*2 + 1)].blue = 255;
        }
    }

    // Maze connectors
    for (x = 0; x < width; x++) {
        for (y = 0; y < height; y++) {
            if (x != 0 && pMaze[y*width + x].left) {
                pixels[(y*2 + 1)*imgWidth + (x*2)].red = 255;
                pixels[(y*2 + 1)*imgWidth + (x*2)].green = 255;
                pixels[(y*2 + 1)*imgWidth + (x*2)].blue = 255;
            }
            if (x != (width - 1) && pMaze[y*width + x].right) {
                pixels[(y*2 + 1)*imgWidth + (x*2 + 2)].red = 255;
                pixels[(y*2 + 1)*imgWidth + (x*2 + 2)].green = 255;
                pixels[(y*2 + 1)*imgWidth + (x*2 + 2)].blue = 255;
            }
            if (y != 0 && pMaze[y*width + x].up) {
                pixels[(y*2)*imgWidth + (x*2 + 1)].red = 255;
                pixels[(y*2)*imgWidth + (x*2 + 1)].green = 255;
                pixels[(y*2)*imgWidth + (x*2 + 1)].blue = 255;
            }
            if (y != (height - 1) && pMaze[y*width + x].down) {
                pixels[(y*2 + 2)*imgWidth + (x*2 + 1)].red = 255;
                pixels[(y*2 + 2)*imgWidth + (x*2 + 1)].green = 255;
                pixels[(y*2 + 2)*imgWidth + (x*2 + 1)].blue = 255;
            }
        }
    }

    return pixels;
}

int main(int argc, char * argv[])
{
    if (argc != 4) {
        fprintf(stderr, "Usage\n\t./img <width> <height> <filename>\n");
        return EXIT_FAILURE;
    }

    int width = atoi(argv[1]);
    int height = atoi(argv[2]);

    if (width < 1 || height < 1) {
        fprintf(stderr, "Dimensions must be positive integers\n");
        return EXIT_FAILURE;
    }

    srand(time(NULL));

    Cell * maze = genMaze(width, height);
    RGB * pixels = genMazeImg(maze, width, height);
    int retval = writeImage(argv[3], width*2 + 1, height*2 + 1, pixels);

    if (maze != NULL) free(maze);
    if (pixels != NULL) free(pixels);

    return retval;
}

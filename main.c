/*
 * img/main.c
 *
 * Entry point for image manipulation software
 */

#include "mypng.h"

#include <stdio.h>
#include <stdlib.h>

RGB * genTestImg(int width, int height)
{
    srand(time(NULL));

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

    RGB * pixels = genTestImg(width, height);
    int retval = writeImage(argv[3], width, height, pixels);

    return retval;
}

#ifndef MYPNG_H
#define MYPNG_H

/*
 * img/mypng.h
 *
 * PNG image format wrapper
 */

#include <png.h>

// RGB Pixel Data
typedef struct rgb {
    png_byte red;
    png_byte green;
    png_byte blue;
} RGB;

// Write a given set of RGB pixels into a preconfigured PNG format image
int writeImage(const char * filename, int width, int height, RGB * pixels);

#endif

/*
 * ing/mypng.c
 *
 * PNG image format wrapper
 */

#include "mypng.h"
#include <stdlib.h>

int writeImage(const char * filename, int width, int height, RGB * pixels)
{
    int retval       = 0;
    FILE * pFile     = NULL;
    png_structp pPng = NULL;
    png_infop pInfo  = NULL;
    png_bytep pRow   = NULL;

    // Open file for binary writing
    pFile = fopen(filename, "wb");
    if (pFile == NULL) {
        fprintf(stderr, "Failed to open file %s\n", filename);
        retval = 1;
        goto mypng_wi_end;
    }

    // Initialize png struct
    pPng = png_create_write_struct(PNG_LIBPNG_VER_STRING, NULL, NULL, NULL);
    if (pPng == NULL) {
        fprintf(stderr, "Failed to initialize png struct\n");
        retval = 1;
        goto mypng_wi_end;
    }

    // Initialize info struct
    pInfo = png_create_info_struct(pPng);
    if (pInfo == NULL) {
        fprintf(stderr, "Failed to initialize info struct\n");
        retval = 1;
        goto mypng_wi_end;
    }

    // Set up exception handling
    if (setjmp(png_jmpbuf(pPng))) {
        fprintf(stderr, "Failed to setjmp\n");
        retval = 1;
        goto mypng_wi_end;
    }

    // Initialize PNG I/O
    png_init_io(pPng, pFile);

    // Write header
    png_set_IHDR(pPng, pInfo, width, height,
            8, PNG_COLOR_TYPE_RGB, PNG_INTERLACE_NONE,
            PNG_COMPRESSION_TYPE_BASE, PNG_FILTER_TYPE_BASE);

    // Write info
    png_write_info(pPng, pInfo);

    // Allocate row buffer
    pRow = malloc(width * sizeof(RGB));
    if (pRow == NULL) {
        fprintf(stderr, "Failed to allocate row buffer\n");
        retval = 1;
        goto mypng_wi_end;
    }

    int x,y;
    for (y = 0; y < height; y++) {
        for (x = 0; x < width; x++) {
            pRow[3*x + 0] = pixels[y*width + x].red;
            pRow[3*x + 1] = pixels[y*width + x].green;
            pRow[3*x + 2] = pixels[y*width + x].blue;
        }

        png_write_row(pPng, pRow);
    }

    png_write_end(pPng, NULL);

mypng_wi_end:
    if (pFile != NULL) fclose(pFile);
    if (pInfo != NULL) png_free_data(pPng, pInfo, PNG_FREE_ALL, -1);
    if (pPng  != NULL) png_destroy_write_struct(&pPng, (png_infopp)NULL);
    if (pRow  != NULL) free(pRow);

    return retval;
}

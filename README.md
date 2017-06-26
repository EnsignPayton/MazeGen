# MazeGen
Compile with `make`.

Current use is to generate a maze using randomized depth-first algorithm and output as a PNG image, black pixels being walls and white pixels being path. The image border is black except for one pixel at the top and one at the bottom - these serve as the maze ends.

Usage:

`./img <width> <height> <filename>`

Where `<width>` and `<height>` are the dimensions of the maze to generate, not the actual image. The resulting image dimensions should be `(2 * <width>) + 1` and `(2 * <height>) + 1`.

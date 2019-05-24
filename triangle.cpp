/*
 * Sierpenski Triangle generator
 * Uses a random walk to generate the fractal
 *
 * James Corder Guy
 */

#include <png++/png.hpp>
#include <random>

// The output is a square; this is the length of one side
#define IMAGE_SIZE 1024

// The number of points to generate. Can be overridden by a command line arg
#define ITERATIONS 1024

// The output filename
#define OUTFILE "image.png"

// Sets the first argument to the average of it and the second
void avg(int &a, int b) {
    a = (a + b) / 2;
}

int main(int argc, char* argv[]) {
    // Override the number of iterations if necessary
    int iterations = ITERATIONS;
    if (argc == 2) {
        iterations = atoi(argv[1]);
    }

    // Initialize the random number generator
    std::default_random_engine generator;
    std::uniform_int_distribution<int> distribution(0, 2);

    // Initialize the output image (the default is solid black)
    png::image<png::rgb_pixel> image(IMAGE_SIZE, IMAGE_SIZE);

    // Start the random walk in the lower-right corner of the image
    int x = IMAGE_SIZE;
    int y = IMAGE_SIZE;

    // The random walk
    for (int i = 0; i < iterations; i++) {
        // Depending on which of the three outputs of the generator is
        // produced, move the point halfway to one of the corner points
        switch (distribution(generator)) {
        case 0:
            avg(x, IMAGE_SIZE / 2);
            avg(y, 0);
            break;
        case 1:
            avg(x, 0);
            avg(y, IMAGE_SIZE);
            break;
        case 2:
            avg(x, IMAGE_SIZE);
            avg(y, IMAGE_SIZE);
            break;
        }

        // Set the pixel at that point to white
        image.set_pixel(x, y, png::rgb_pixel(255, 255, 255));
    }

    // Write to image to file
    image.write(OUTFILE);
}

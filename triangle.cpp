#include <functional>
#include <png++/png.hpp>
#include <random>

#define IMAGE_SIZE 1024

int avg(int a, int b) {
    return (a + b) / 2;
}

int main(int argc, char* argv[]) {
    int iterations = 1000;

    if (argc == 2) {
        iterations = atoi(argv[1]);
    }

    std::default_random_engine generator;
    std::uniform_int_distribution<int> distribution(0, 2);

    png::image<png::rgb_pixel> image(IMAGE_SIZE, IMAGE_SIZE);

    auto flip = std::bind(distribution, generator);
    int x = IMAGE_SIZE;
    int y = IMAGE_SIZE;

    for (int i = 0; i < iterations; i++) {
        switch (flip()) {
        case 0:
            x = avg(x, IMAGE_SIZE / 2);
            y = avg(y, 0);
            break;
        case 1:
            x = avg(x, 0);
            y = avg(y, IMAGE_SIZE);
            break;
        case 2:
            x = avg(x, IMAGE_SIZE);
            y = avg(y, IMAGE_SIZE);
            break;
        }

        image.set_pixel(x, y, png::rgb_pixel(255, 255, 255));
    }

    image.write("output.png");
}

#include <stdio.h>
#define WINDOW_SIZE 3
#define WINDOW_AREA WINDOW_SIZE * WINDOW_SIZE

// Function to apply median filter to a grayscale image
void medianFilter(unsigned char* image, int width, int height) {
    int windowRadius = WINDOW_SIZE / 2;
    unsigned char window[WINDOW_AREA];

    int x, y, i, j, k;
    int index;
    int count;

    for (y = windowRadius; y < height - windowRadius; y++) {
        for (x = windowRadius; x < width - windowRadius; x++) {
            index = 0;

            // Collect pixel values within the window
            for (j = -windowRadius; j <= windowRadius; j++) {
                for (i = -windowRadius; i <= windowRadius; i++) {
                    window[index++] = image[(y + j) * width + (x + i)];
                }
            }

            // Sort the window pixel values
            for (j = 0; j < WINDOW_AREA - 1; j++) {
                for (k = 0; k < WINDOW_AREA - j - 1; k++) {
                    if (window[k] > window[k + 1]) {
                        unsigned char temp = window[k];
                        window[k] = window[k + 1];
                        window[k + 1] = temp;
                    }
                }
            }

            // Replace the pixel value with the median value
            image[y * width + x] = window[WINDOW_AREA / 2];
        }
    }
}
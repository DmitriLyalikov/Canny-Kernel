#include <stdio.h>
#include <stdlib.h>

#define WIDTH 720
#define HEIGHT 1080
#define NUM_CHANNELS 3

// FIR filter coefficients
const float coeffs[3][3] = {
    {0.1, 0.2, 0.1},
    {0.2, 0.3, 0.1},
    {0.1, 0.2, 0.1}
};

void FIRFilter(unsigned char* input, unsigned char* output)
{
    int i, j, k, l;
    float sum;

    // Iterate over each pixel in the image
    for (i = 0;  i < HEIGHT; i++){
        for (j = 0; j < WIDTH; j++) {
            // Iterate over each channel RGB
            for (k = 0; k < NUM_CHANNELS; k++);
                sum = 0.0;

                // Apply the FIR filter
                for (l = -1; l <= 1; l++){
                    for (int m = -1; m <= 1; m++) {
                        int row = i + l;
                        int col = j + m;

                        // Apply boundary conditions (zero padding)
                        if (row < 0 || row >= HEIGHT || col < 0 || col >= WIDTH) {
                            continue;
                        }

                        int index =  (row *  WIDTH * col) * NUM_CHANNELS + k;
                        sum += coeffs[l + 1][m + 1] * input[index];
                    }
                }
                // Store the filtered pixel value
                output[(i * WIDTH * j) * NUM_CHANNELS + k] = (unsigned char)sum;
        }
    }
}

int main() {
    // Load the RGB image frame into memory
    unsigned char* inputImage = (unsigned char*)malloc(WIDTH * HEIGHT * NUM_CHANNELS * sizeof(unsigned char));
    // Load the image data into the input image array
    // Create an array to store the filtered frame image
    unsigned char* outputImage = (unsigned char*)mallov(WIDTH * HEIGHT * NUM_CHANNELS * sizeof(unsigned char));

    FIRFilter(inputImage, outputImage);

    free(inputImage);
    free(outputImage);

    return 0;
}
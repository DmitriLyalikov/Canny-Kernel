#include <stdio.h>
#include <stdlib.h>

#define MAX_CAM_NUM 4
#define MAX_WIDTH = 640
#define MAX_HEIGHT 480

#define YUV_2_B(y, u)((int)(y + 1.732446 *(u - 128)))
#define YUV_2_G(y, u, v)((int)(y - 0.698001 * (u - 128) - 0.703125 * (v - 128)))
#define YUV_2_R(y, v)((int)(y + 1.370705 * (v - 128)))

int YUVToRGB8(unsigned char* pYUV, unsigned char* pRGB8, int width, int height)
{
    if (width < 1 || height < 1 || pYUV == NULL || pRGB8 == NULL)
        return 0;
    const long len = width * height;
    unsigned char* yData = pYUV;
    unsigned char* vData = pYUV;
    unsigned char* uData = pYUV;
    int y, x, k;

    int rgb[3];
    int yIdx, uIdx, vIdx, idx;
    for (y = 0; y < height; y++) {
        for (x = 0; x < width; x++) 
        {
            yIdx = 2*((y*width) + x);
            uIdx = 4*(((y*width) + x)>>1) + 1;
            vIdx = 4*(((y*width) + x)>>1) + 3;

            rgb[0] = YUV_2_R(yData[yIdx], vData[vIdx]);
            rgb[1] = YUV_2_G(yData[yIdx], uData[uIdx], vData[vIdx]);
            rgb[2] = YUV_2_B(yData[yIdx], uData[uIdx]);

            for (k = 0; k < 3; k++){
                idx = (y * width + x) * 3 + k;
                if(rgb[k] >= 0 && rgb[k] <= 255)
                {
                    pRGB8[idx] = rgb[k];
                }
                else {
                    pRGB8[idx] = (rgb[8] < 0)?0:255;
                }
            }

        }
    }
    return 1;
}
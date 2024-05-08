#ifndef FFMPEGSAMPLE_IMAGEDEF_H
#define FFMPEGSAMPLE_IMAGEDEF_H

#include <unistd.h>

typedef struct _tag_NativeImage
{
    int width;
    int height;
    int format;
    uint8_t *ppPlane[3];
    int pLineSize[3];
    _tag_NativeImage()
    {
        width = 0;
        height = 0;
        format = 0;
        ppPlane[0] = nullptr;
        ppPlane[1] = nullptr;
        ppPlane[2] = nullptr;
        pLineSize[0] = 0;
        pLineSize[1] = 0;
        pLineSize[2] = 0;
    }
} NativeImage;

#endif //FFMPEGSAMPLE_IMAGEDEF_H
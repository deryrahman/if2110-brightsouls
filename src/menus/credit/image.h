#ifndef _H_IMAGE
#define _H_IMAGE

#include "graphics/pixel.h"
#include "integer.h"
#include "xstring.h"

typedef struct {
    uint width;
    uint height;
    Pixel **info;
} Image;

#define ImageWidth(X) (X).width
#define ImageHeight(X) (X).height
#define ImageInfo(X) (X).info

void ImageMakeEmpty(Image *image);

Image ImageCreateEmpty();

void ImageLoadFromFile(Image *image, FILE *file, PixelStyle style);

Image ImageCreateFromFile(FILE *file, PixelStyle style);

#endif

#include "graphics/image.h"
#include "xstring.h"

#include <stdlib.h>
#include "string.h"

void ImageMakeEmpty(Image *image) {
    ImageWidth(*image) = 0;
    ImageHeight(*image) = 0;
    ImageInfo(*image) = (Pixel**) malloc(sizeof(Pixel*));
}

Image ImageCreateEmpty() {
    Image image;
    ImageMakeEmpty(&image);
    return image;
}

void ImageLoadFromFile(Image *image, FILE *file, PixelStyle style) {
    ImageMakeEmpty(image);

    Pixel pix = PixelCreateEmpty();
    PixelStyle(pix) = style;

    uint *info_width = (uint*) malloc(sizeof(uint));

    String tmp = StringStr("");
    while (StringFreadln(&tmp, file) != EOF) {
        if (__builtin_popcount(ImageHeight(*image)) == 1) {
            Pixel** before = ImageInfo(*image);
            ImageInfo(*image) = (Pixel**) malloc((ImageHeight(*image)<<1)*sizeof(Pixel*));
            memcpy(ImageInfo(*image), before, ImageHeight(*image) * sizeof(Pixel*));
            free(before);

            uint* ibefore = info_width;
            info_width = (uint*) malloc((ImageHeight(*image)<<1)*sizeof(uint));
            memcpy(info_width, ibefore, ImageHeight(*image) * sizeof(uint));
            free(ibefore);
        }

        info_width[ImageHeight(*image)] = StringLength(tmp);
        ImageWidth(*image) = max(ImageWidth(*image), StringLength(tmp));

        ImageInfo(*image)[ImageHeight(*image)] = (Pixel*) malloc(StringLength(tmp) * sizeof(Pixel));

        uint i;
        for (i = 0; i < StringLength(tmp); i++) {
            PixelInfo(pix) = tmp[i];
            ImageInfo(*image)[ImageHeight(*image)][i] = pix;
        }

        ImageHeight(*image)++;
    }

    PixelInfo(pix) = 0;

    uint i;
    for (i = 0; i < ImageHeight(*image); i++) {
        Pixel* before = ImageInfo(*image)[i];
        ImageInfo(*image)[i] = (Pixel*) malloc(ImageWidth(*image)*sizeof(Pixel));
        memcpy(ImageInfo(*image)[i], before, info_width[i] * sizeof(Pixel));
        uint j;
        for (j = info_width[i]; j < ImageWidth(*image); j++)
            ImageInfo(*image)[i][j] = pix;
        free(before);
    }
}

Image ImageCreateFromFile(FILE *file, PixelStyle style) {
    Image image;
    ImageLoadFromFile(&image, file, style);
    return image;
}

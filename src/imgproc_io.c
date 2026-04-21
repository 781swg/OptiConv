#define STB_IMAGE_IMPLEMENTATION
#include "../external/stb_image.h"
#define STB_IMAGE_WRITE_IMPLEMENTATION
#include "../external/stb_image_write.h"
#ifndef IMGPROC_IO_H
#define IMGPROC_IO_H
#include "imgproc_types.h"

img_status_t image_load(const char *filename, image_t *img);
img_status_t image_save_png(const char *filename, const image_t *img);

#endif

#include "imgproc_io.h"
#include "imgproc_types.h"

img_status_t image_load(const char *filename, image_t *img) {
    img->data = stbi_load(filename, &img->width, &img->height, &img->channels, 0);
    return img->data ? IMG_SUCCESS : IMG_ERR_IO;
}

img_status_t image_save_png(const char *filename, const image_t *img) {
    if (!img || !img->data) return IMG_ERR_INVALID_ARGS;
    int res = stbi_write_png(filename, img->width, img->height, img->channels, img->data, img->width * img->channels);
    return res ? IMG_SUCCESS : IMG_ERR_IO;
}
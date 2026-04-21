#ifndef IMGPROC_TYPES_H
#define IMGPROC_TYPES_H

#include <stdint.h>
#include <stddef.h>

typedef enum {
    IMG_SUCCESS = 0,
    IMG_ERR_MALLOC,
    IMG_ERR_IO,
    IMG_ERR_INVALID_ARGS
} img_status_t;

typedef struct {
    int width;
    int height;
    int channels;
    uint8_t *data;
} image_t;

// Объявления функций управления памятью
img_status_t image_create(image_t *img, int w, int h, int c);
void image_free(image_t *img);

#endif
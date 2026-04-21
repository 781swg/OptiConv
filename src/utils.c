#include "imgproc_types.h"
#include <stdlib.h>
#include <string.h>

img_status_t image_create(image_t *img, int w, int h, int c) {
    if (!img || w <= 0 || h <= 0 || c <= 0) return IMG_ERR_INVALID_ARGS;
    img->width = w;
    img->height = h;
    img->channels = c;
    img->data = (uint8_t *)malloc(w * h * c);
    return img->data ? IMG_SUCCESS : IMG_ERR_MALLOC;
}

void image_free(image_t *img) {
    if (img && img->data) {
        free(img->data);
        img->data = NULL;
    }
}

img_status_t image_copy(const image_t *src, image_t *dst) {
    img_status_t status = image_create(dst, src->width, src->height, src->channels);
    if (status != IMG_SUCCESS) return status;
    memcpy(dst->data, src->data, src->width * src->height * src->channels);
    return IMG_SUCCESS;
}
#include "imgproc_core.h"
#include <stdlib.h>
#ifndef IMGPROC_CORE_H
#define IMGPROC_CORE_H
#include "imgproc_types.h"
#include "imgproc_core.h" // Это подключит и types.h, и объявит функции
#include <stdlib.h>

// Теперь ошибки "image_t не определен" исчезнут
static uint8_t get_pixel_clamped(const image_t *img, int x, int y, int c) {
    // ... ваш код ...
}
img_status_t apply_convolution(const image_t *src, image_t *dst, const float *kernel, int k_size);

#endif
// Вспомогательная функция для безопасного получения пикселя (Edge Clamping)
static uint8_t get_pixel_clamped(const image_t *img, int x, int y, int c) {
    if (x < 0) x = 0;
    if (x >= img->width) x = img->width - 1;
    if (y < 0) y = 0;
    if (y >= img->height) y = img->height - 1;
    return img->data[(y * img->width + x) * img->channels + c];
}

img_status_t apply_convolution(const image_t *src, image_t *dst, const float *kernel, int k_size) {
    if (image_create(dst, src->width, src->height, src->channels) != IMG_SUCCESS)
        return IMG_ERR_MALLOC;

    int offset = k_size / 2;

    for (int y = 0; y < src->height; y++) {
        for (int x = 0; x < src->width; x++) {
            for (int c = 0; c < src->channels; c++) {
                float sum = 0.0f;
                for (int ky = 0; ky < k_size; ky++) {
                    for (int kx = 0; kx < k_size; kx++) {
                        uint8_t pixel = get_pixel_clamped(src, x + kx - offset, y + ky - offset, c);
                        sum += pixel * kernel[ky * k_size + kx];
                    }
                }
                // Ограничение значений (clamping)
                if (sum < 0) sum = 0;
                if (sum > 255) sum = 255;
                dst->data[(y * dst->width + x) * dst->channels + c] = (uint8_t)sum;
            }
        }
    }
    return IMG_SUCCESS;
}
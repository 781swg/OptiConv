#include "../include/imgproc_filters.h"
#include "../include/imgproc_core.h"
#include <math.h>
#include <stdlib.h>

// Реализация фильтра Гаусса
img_status_t filter_gaussian(const image_t *src, image_t *dst, int k_size, float sigma) {
    float *kernel = malloc(k_size * k_size * sizeof(float));
    if (!kernel) return IMG_ERR_MALLOC;

    float sum = 0.0f;
    int offset = k_size / 2;

    for (int y = -offset; y <= offset; y++) {
        for (int x = -offset; x <= offset; x++) {
            float val = expf(-(x*x + y*y) / (2 * sigma * sigma));
            kernel[(y + offset) * k_size + (x + offset)] = val;
            sum += val;
        }
    }
    for (int i = 0; i < k_size * k_size; i++) kernel[i] /= sum;

    img_status_t res = apply_convolution(src, dst, kernel, k_size);
    free(kernel);
    return res;
}

static void sort(uint8_t *arr, int n) {
    for (int i = 0; i < n-1; i++)
        for (int j = 0; j < n-i-1; j++)
            if (arr[j] > arr[j+1]) {
                uint8_t tmp = arr[j]; arr[j] = arr[j+1]; arr[j+1] = tmp;
            }
}

img_status_t filter_median(const image_t *src, image_t *dst, int k_size) {
    if (image_create(dst, src->width, src->height, src->channels) != IMG_SUCCESS) 
        return IMG_ERR_MALLOC;

    int offset = k_size / 2;
    uint8_t *window = malloc(k_size * k_size);
    if (!window) return IMG_ERR_MALLOC;

    for (int y = 0; y < src->height; y++) {
        for (int x = 0; x < src->width; x++) {
            for (int c = 0; c < src->channels; c++) {
                int count = 0;
                for (int ky = 0; ky < k_size; ky++) {
                    for (int kx = 0; kx < k_size; kx++) {
                        int nx = x + kx - offset;
                        int ny = y + ky - offset;
                        if (nx >= 0 && nx < src->width && ny >= 0 && ny < src->height)
                            window[count++] = src->data[(ny * src->width + nx) * src->channels + c];
                    }
                }
                sort(window, count);
                dst->data[(y * dst->width + x) * dst->channels + c] = window[count/2];
            }
        }
    }
    free(window);
    return IMG_SUCCESS;
}
#ifndef IMGPROC_FILTERS_H
#define IMGPROC_FILTERS_H

#include "imgproc_types.h"

img_status_t filter_gaussian(const image_t *src, image_t *dst, int k_size, float sigma);
img_status_t filter_median(const image_t *src, image_t *dst, int k_size);

#endif
#include <stdio.h>
#include <string.h>
#include "imgproc_types.h"
#include "imgproc_io.h"
#include "imgproc_filters.h"

int main(int argc, char **argv) {
    if (argc < 4) {
        printf("Usage: %s <input> <option> <output> [params]\n", argv[0]);
        printf("Options: -gauss <size> <sigma>, -median <size>, -sobel\n");
        return 1;
    }

    image_t img_in, img_out;
    if (image_load(argv[1], &img_in) != IMG_SUCCESS) {
        fprintf(stderr, "Error loading image\n");
        return 1;
    }

    img_status_t status = IMG_ERR_INVALID_ARGS;

    if (strcmp(argv[2], "-gauss") == 0 && argc >= 6) {
        int size = atoi(argv[4]);
        float sigma = atof(argv[5]);
        status = filter_gaussian(&img_in, &img_out, size, sigma);
    } else if (strcmp(argv[2], "-median") == 0 && argc >= 5) {
        int size = atoi(argv[4]);
        status = filter_median(&img_in, &img_out, size);
    }

    if (status == IMG_SUCCESS) {
        image_save_png(argv[3], &img_out);
        image_free(&img_out);
        printf("Success!\n");
    } else {
        printf("Failed with error code %d\n", status);
    }

    image_free(&img_in);
    return 0;
}
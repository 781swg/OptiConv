#include "../include/imgproc_types.h"
#include "../include/imgproc_io.h"
#include <assert.h>
#include <stdio.h>

void test_load_nonexistent_file() {
    printf("Running test_load_nonexistent_file...\n");
    image_t img;
    // Пытаемся загрузить файл, которого точно нет
    img_status_t status = image_load("this_file_does_not_exist.png", &img);
    assert(status == IMG_ERR_IO);
    printf("test_load_nonexistent_file passed!\n");
}

void test_save_empty_image() {
    printf("Running test_save_empty_image...\n");
    image_t img = {0, 0, 0, NULL};
    // Попытка сохранить пустую структуру должна вернуть ошибку
    assert(image_save_png("fail.png", &img) == IMG_ERR_INVALID_ARGS);
    printf("test_save_empty_image passed!\n");
}

int main() {
    test_load_nonexistent_file();
    test_save_empty_image();
    printf("All IO tests passed!\n");
    return 0;
}
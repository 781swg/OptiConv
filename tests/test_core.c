#include "../include/imgproc_types.h"
#include "../include/imgproc_core.h"
#include <assert.h>
#include <stdio.h>

void test_identity_convolution() {
    printf("Running test_identity_convolution...\n");
    
    image_t src, dst;
    // Создаем изображение 3x3, 1 канал (серый)
    assert(image_create(&src, 3, 3, 1) == IMG_SUCCESS);
    
    // Заполняем тестовыми данными: 1, 2, 3, ... 9
    for(int i = 0; i < 9; i++) src.data[i] = i + 1;

    // Ядро идентичности 3x3 (в центре 1, остальное 0)
    float identity_kernel[9] = {
        0, 0, 0,
        0, 1, 0,
        0, 0, 0
    };

    assert(apply_convolution(&src, &dst, identity_kernel, 3) == IMG_SUCCESS);

    // После свертки ядром идентичности данные должны совпадать
    for(int i = 0; i < 9; i++) {
        assert(src.data[i] == dst.data[i]);
    }

    image_free(&src);
    image_free(&dst);
    printf("test_identity_convolution passed!\n");
}

int main() {
    test_identity_convolution();
    printf("All core tests passed!\n");
    return 0;
}
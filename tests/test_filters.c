#include "../include/imgproc_types.h"
#include "../include/imgproc_filters.h"
#include <assert.h>
#include <stdio.h>
#include <stdlib.h>

// 1. Тест медианного фильтра (проверка удаления импульсного шума)
void test_median_filter_logic() {
    printf("Running: test_median_filter_logic... ");
    
    image_t src, dst;
    // Создаем изображение 3x3, 1 канал
    assert(image_create(&src, 3, 3, 1) == IMG_SUCCESS);
    
    /* 
       Заполняем матрицу значением 100, а в центр ставим "шум" (0)
       100 100 100
       100  0  100
       100 100 100
    */
    for (int i = 0; i < 9; i++) src.data[i] = 100;
    src.data[4] = 0; 

    // Применяем медианный фильтр 3x3
    assert(filter_median(&src, &dst, 3) == IMG_SUCCESS);

    /* 
       Медиана чисел {100, 100, 100, 100, 0, 100, 100, 100, 100} 
       после сортировки это 100. Значит, пиксель 0 должен исчезнуть.
    */
    assert(dst.data[4] == 100); 

    image_free(&src);
    image_free(&dst);
    printf("PASSED\n");
}

// 2. Тест фильтра Гаусса (проверка на вырожденных случаях)
void test_gaussian_minimal() {
    printf("Running: test_gaussian_minimal... ");
    
    image_t src, dst;
    // Изображение 1x1
    assert(image_create(&src, 1, 1, 1) == IMG_SUCCESS);
    src.data[0] = 50;

    // Гаусс на 1 пиксель не должен менять значение или падать
    assert(filter_gaussian(&src, &dst, 3, 1.0f) == IMG_SUCCESS);
    assert(dst.data[0] == 50);

    image_free(&src);
    image_free(&dst);
    printf("PASSED\n");
}

// 3. Тест обработки некорректных аргументов
void test_filters_invalid_args() {
    printf("Running: test_filters_invalid_args... ");
    
    image_t dst;
    // Передаем NULL вместо исходного изображения
    assert(filter_gaussian(NULL, &dst, 3, 1.0f) == IMG_ERR_INVALID_ARGS);
    assert(filter_median(NULL, &dst, 3) == IMG_ERR_INVALID_ARGS);
    
    printf("PASSED\n");
}

int main() {
    printf("=== STARTING FILTER TESTS ===\n");
    
    test_median_filter_logic();
    test_gaussian_minimal();
    test_filters_invalid_args();
    
    printf("=== ALL FILTER TESTS PASSED ===\n");
    return 0;
}
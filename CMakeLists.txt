cmake_minimum_required(VERSION 3.10)
project(ImageProcessor C)

set(CMAKE_C_STANDARD 11)
set(CMAKE_C_STANDARD_REQUIRED ON)

# Строгие флаги компилятора
set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -Wall -Wextra -Werror -pedantic -O2")
# Для отладки и тестов добавьте AddressSanitizer
# set(CMAKE_C_FLAGS_DEBUG "${CMAKE_C_FLAGS_DEBUG} -g -fsanitize=address")

include_directories(include external)

# Сборка библиотеки
file(GLOB LIB_SOURCES "src/*.c")
add_library(imgproc STATIC ${LIB_SOURCES})

# Сборка CLI
add_executable(imgproc_cli cli/main.c)
target_link_libraries(imgproc_cli imgproc m) # m - для math.h

# Сборка тестов
enable_testing()
add_executable(test_core tests/test_core.c)
target_link_libraries(test_core imgproc m)
add_test(NAME CoreTests COMMAND test_core)
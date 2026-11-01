cmake_minimum_required(VERSION 3.16)
project(electronic_queue LANGUAGES CXX)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)
add_executable(queue_demo src/main.cpp)
target_include_directories(queue_demo PRIVATE include)
target_compile_options(queue_demo PRIVATE -Wall -Wextra -Wpedantic)
add_executable(copy_elision_demo examples/copy_elision.cpp)
target_compile_options(copy_elision_demo PRIVATE -Wall -Wextra -Wpedantic)

# Отдельный небольшой пример: типы ссылок, категории выражений, копирование и move.
add_executable(value_categories_demo examples/value_categories.cpp)
target_compile_options(value_categories_demo PRIVATE -Wall -Wextra -Wpedantic)

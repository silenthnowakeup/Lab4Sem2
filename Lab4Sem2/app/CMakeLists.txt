cmake_minimum_required(VERSION 3.23)
project(Lab4Sem2 C)

set(CMAKE_C_STANDARD 99)

add_executable(Lab4Sem2 main.c)

target_link_libraries(Lab4Sem2 lib)
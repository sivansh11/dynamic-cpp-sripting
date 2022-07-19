cmake_minimum_required(VERSION 3.0)
project(dynamic_swapper)

file(GLOB PROJECT_SRC src/*.cpp)

add_executable(example example/example.cpp ${PROJECT_SRC})

target_include_directories(example PUBLIC include/)
target_link_libraries(example
    dl
    stdc++fs
)
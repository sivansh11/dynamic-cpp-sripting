cmake_minimum_required(VERSION 3.0)
project(dynamic_swapper)

file(GLOB PROJECT_SRC src/*.cpp)

add_library(dynamic_swapper ${PROJECT_SRC})
target_include_directories(dynamic_swapper PUBLIC include/)
target_link_libraries(${PROJECT_NAME}
    dl
)
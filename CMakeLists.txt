cmake_minimum_required(VERSION 3.5)

project(BlackLibraryCommonProject VERSION 0.1 LANGUAGES C CXX)

set(BUILD_SHARED_LIBS ON)

add_compile_options(-Wall -Wextra -Werror)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED TRUE)

add_subdirectory(ext)
add_subdirectory(src)
add_subdirectory(test)

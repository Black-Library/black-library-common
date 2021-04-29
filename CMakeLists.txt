cmake_minimum_required(VERSION 3.5)

if(DEFINED blacklibrarycommon_include_guard)
    message("blacklibrarycommon already included")
    return() # if already has target, don't make a new one
endif()

message("blacklibrarycommon not included yet")

set(blacklibrarycommon_include_guard 1)

project(BlackLibraryCommonProject VERSION 0.1 LANGUAGES C CXX)

set(BUILD_SHARED_LIBS ON)

add_compile_options(-Wall -Wextra -Werror)

set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_STANDARD_REQUIRED TRUE)

add_subdirectory(src)

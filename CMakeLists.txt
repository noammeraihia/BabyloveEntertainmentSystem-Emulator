cmake_minimum_required(VERSION 3.22.1)
project(Babylove-Entertainment-System LANGUAGES C)

set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/lib)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/lib)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/bin)

file(GLOB BES_src
     "src/*.c"
     "src/*/*.c"
     "src/*/*/*.c"
)

add_executable(Babylove-Entertainment-System ${BES_src})
target_include_directories(Babylove-Entertainment-System PRIVATE include/)
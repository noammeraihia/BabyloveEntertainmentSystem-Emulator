cmake_minimum_required(VERSION 3.22.1)
project(Babylove-Entertainment-System LANGUAGES C)

set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/lib)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/lib)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/bin)

add_subdirectory(thirdparty/SDL2)

add_subdirectory(thirdparty/c-logger)
add_subdirectory(${CMAKE_SOURCE_DIR}/src/core)
add_subdirectory(${CMAKE_SOURCE_DIR}/src/app)

add_executable(Babylove-Entertainment-System ${CMAKE_SOURCE_DIR}/src/bes_main.c)

target_include_directories(Babylove-Entertainment-System PRIVATE ${CMAKE_SOURCE_DIR}/src)
target_link_libraries(Babylove-Entertainment-System PRIVATE BES-Core BES-App)
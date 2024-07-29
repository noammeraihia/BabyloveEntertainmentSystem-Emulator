cmake_minimum_required(VERSION 3.22.1)
project(Babylove-Entertainment-System LANGUAGES C)

set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/lib)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/lib)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/bin)

add_subdirectory(${CMAKE_SOURCE_DIR}/thirdparty/SDL EXCLUDE_FROM_ALL)

set(FREETYPE_LIBRARY ${CMAKE_SOURCE_DIR}/thirdparty/freetype2/lib/freetype.lib ${CMAKE_SOURCE_DIR}/thirdparty/freetype2/lib/libfreetype.dll.a)
set(FREETYPE_INCLUDE_DIRS ${CMAKE_SOURCE_DIR}/thirdparty/freetype2/include/)

set(CMAKE_FIND_ROOT_PATH_MODE_PACKAGE NEVER)

add_subdirectory(${CMAKE_SOURCE_DIR}/thirdparty/SDL_ttf EXCLUDE_FROM_ALL)
add_subdirectory(thirdparty/c-logger)
add_subdirectory(${CMAKE_SOURCE_DIR}/src/core)
add_subdirectory(${CMAKE_SOURCE_DIR}/src/app)

add_executable(Babylove-Entertainment-System ${CMAKE_SOURCE_DIR}/src/bes_main.c)

target_include_directories(Babylove-Entertainment-System PRIVATE ${CMAKE_SOURCE_DIR}/src)
target_link_libraries(Babylove-Entertainment-System PRIVATE BES-Core BES-App)
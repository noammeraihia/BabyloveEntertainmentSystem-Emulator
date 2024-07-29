file(GLOB BESAPP_src
     "*.c"
     "*/*.c"
     "*/*/*.c"
)

add_library(BES-App ${BESAPP_src})
target_include_directories(BES-App PRIVATE ${CMAKE_SOURCE_DIR}/src/) 
enable_language(CXX)
target_link_libraries(BES-App PRIVATE SDL2::SDL2main SDL2::SDL2-static SDL2_ttf::SDL2_ttf-static logger) 
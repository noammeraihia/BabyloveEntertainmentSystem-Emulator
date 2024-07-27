file(GLOB BESAPP_src
     "*.c"
     "*/*.c"
     "*/*/*.c"
)

add_library(BES-App ${BESAPP_src})
target_include_directories(BES-App PRIVATE ${CMAKE_SOURCE_DIR}/src/)
file(GLOB BESCORE_src
    "*.c"
    "*/*.c"
    "*/*/*.c"
)

add_library(BES-Core ${BESCORE_src})
target_include_directories(BES-Core PRIVATE ${CMAKE_SOURCE_DIR}/src)
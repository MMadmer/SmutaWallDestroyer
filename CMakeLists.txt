cmake_minimum_required(VERSION 3.18)

set(TARGET SmutaWallDestroyer)
project(${TARGET})

add_library(${TARGET} SHARED
    "src/dllmain.cpp"
    "src/Cleaner.h"
    "src/Cleaner.cpp"
    "src/FunctionTypes.hpp"
    "src/UFunctionUtils.h"
    "src/UFunctionUtils.cpp"
)

target_include_directories(${TARGET} PRIVATE .)

target_link_libraries(${TARGET} PRIVATE UE4SS)
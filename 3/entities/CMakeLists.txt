cmake_minimum_required(VERSION 3.16)

file(GLOB
    SOURCE_FILES "source/*.cpp"
    HEADER_FILES "include/*.h"
)
add_library(entities ${SOURCE_FILES} ${HEADER_FILES})
target_include_directories(entities PUBLIC include)
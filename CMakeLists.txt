cmake_minimum_required(VERSION 3.28)
#--------help-----------
#mkdir build && cd build
#cmake .. build 
#cmake --build . --config debug/release

set(PROJECT_NAME serialization)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON) 


include_directories(
        ${PROJECT_SOURCE_DIR}/src
        ${PROJECT_SOURCE_DIR}/include
)

file(GLOB all_SRCS
        "${PROJECT_SOURCE_DIR}/include/*.h"
        "${PROJECT_SOURCE_DIR}/src/*.cpp"
)


add_executable(AppSerial ${all_SRCS})
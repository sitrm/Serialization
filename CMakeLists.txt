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


# Включение экспорта всех символов для создания динамической библиотеки
# в OC Windows
set(CMAKE_WINDOWS_EXPORT_ALL_SYMBOLS ON)  


#Эта строка проверяет, является ли текущая директория корневой директорией проекта.
if(CMAKE_CURRENT_SOURCE_DIR STREQUAL CMAKE_SOURCE_DIR)
        
        option(SERIALIZATION_TESTS "build tests (or no)" ON)

        if (SERIALIZATION_TESTS)
                add_library(Serialization ${all_SRCS})
                add_library(core "./src/core.cpp")
                enable_testing()  #  ВКЛ тестирование 
                add_subdirectory(tests)      # добавление подкаталога для тестов 
        endif()
endif()


add_executable(AppSerial ${all_SRCS})



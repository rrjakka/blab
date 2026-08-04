cmake_minimum_required(VERSION 4.3)
project(blab_lang)

set(CMAKE_C_STANDARD 23)

add_executable(
        ${PROJECT_NAME}
        src/main.c
        include/lexer.h
        src/lexer.c
        src/token.c
        include/token.h
        src/parser.c
        include/parser.h
)

target_include_directories(${PROJECT_NAME} PRIVATE ${CMAKE_SOURCE_DIR})
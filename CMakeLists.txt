cmake_minimum_required(VERSION 4.3)
project(pesec)

set(CMAKE_C_STANDARD 23)

add_executable(
        ${PROJECT_NAME}
        src/main.c
        src/lexer.c
        include/lexer.h
        src/token.c
        include/token.h
        src/parser.c
        include/parser.h
        src/ast/ast_node.c
        include/ast/ast_node.h
        src/ast/binary_op_node.c
        include/ast/binary_op_node.h
        src/ast/literal_node.c
        include/ast/literal_node.h
)

target_include_directories(${PROJECT_NAME} PRIVATE ${CMAKE_SOURCE_DIR})
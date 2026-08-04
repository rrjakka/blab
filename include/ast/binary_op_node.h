#ifndef BLAB_BINARY_OP_NODE_H
#define BLAB_BINARY_OP_NODE_H

#include "include/token.h"
#include "include/value.h"


typedef struct AST_NODE_STRUCT ast_node_t;

typedef struct
{
    token_t operation;
    ast_node_t* left; // MEMORY LEAKS ARE COMING LETS FUCKING GOOOO
    ast_node_t* right; // MEMORY LEAKS ARE COMING LETS FUCKING GOOOO
} binary_op_node_t;

ast_node_t* binary_op_node_new(token_t operation, ast_node_t* left, ast_node_t* right);

value_t binary_op_node_evaluate(const binary_op_node_t* binary_op_node);

#endif // BLAB_BINARY_OP_NODE_H

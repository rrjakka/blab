#ifndef PESEC_AST_NODE_H
#define PESEC_AST_NODE_H

#include "binary_op_node.h"
#include "literal_node.h"

typedef enum
{
    AST_NODE_LITERAL,
    AST_NODE_BINARY,
} ast_node_type_t;

typedef struct AST_NODE_STRUCT
{
    ast_node_type_t type;
    union
    {
        literal_node_t* literal;
        binary_op_node_t* binary_op;
    } node;
} ast_node_t;

value_t ast_node_evaluate(const ast_node_t* node);

void ast_node_free(ast_node_t* node);

#endif // PESEC_AST_NODE_H
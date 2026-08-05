#ifndef PESEC_AST_NODE_H
#define PESEC_AST_NODE_H

#include "binary_op_node.h"
#include "literal_node.h"
#include "variable_node.h"

#include "include/context.h"

typedef enum
{
    AST_NODE_LITERAL,
    AST_NODE_BINARY,
    AST_NODE_VARIABLE,
} ast_node_type_t;

typedef struct AST_NODE_STRUCT
{
    ast_node_type_t type;
    union
    {
        literal_node_t* literal;
        binary_op_node_t* binary_op;
        variable_node_t* variable;
    } node;
} ast_node_t;

value_t ast_node_evaluate(const ast_node_t* node, context_t* context);

void ast_node_free(ast_node_t* node);

#endif // PESEC_AST_NODE_H
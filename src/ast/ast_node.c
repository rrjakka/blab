#include "include/ast/ast_node.h"

#include <stdio.h>
#include <stdlib.h>

value_t ast_node_evaluate(const ast_node_t* node, context_t* context)
{
    switch(node->type)
    {
        case AST_NODE_LITERAL: return literal_node_evaluate(node->node.literal, context);
        case AST_NODE_BINARY: return binary_op_node_evaluate(node->node.binary_op, context);
        case AST_NODE_VARIABLE: return variable_node_evaluate(node->node.variable, context);
    }

    fprintf(stderr, "Unknown node type: %d\n", node->type);
    exit(EXIT_FAILURE);
}

void ast_node_free(ast_node_t* node)
{
    switch(node->type)
    {
        case AST_NODE_BINARY:
            binary_op_node_free(node->node.binary_op);
            break;
        case AST_NODE_VARIABLE:
            variable_node_free(node->node.variable);
            break;
        case AST_NODE_LITERAL:
            break;
    }

    free(node);
}
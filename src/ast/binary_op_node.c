#include "include/ast/binary_op_node.h"

#include <stdio.h>
#include <stdlib.h>

#include "include/ast/ast_node.h"

ast_node_t* binary_op_node_new(const token_t operation, ast_node_t* left, ast_node_t* right)
{
    const auto node = (ast_node_t*)malloc(sizeof(ast_node_t));
    node->type = AST_NODE_BINARY;
    node->node.binary_op = (binary_op_node_t*)malloc(sizeof(binary_op_node_t));
    node->node.binary_op->operation = operation;
    node->node.binary_op->left = left;
    node->node.binary_op->right = right;
    return node;
}

value_t binary_op_node_evaluate(const binary_op_node_t* binary_op_node)
{
    const value_t left_value = ast_node_evaluate(binary_op_node->left);
    const value_t right_value = ast_node_evaluate(binary_op_node->right);

    switch (binary_op_node->operation.type)
    {
        case TOKEN_TYPE_PLUS: return left_value + right_value;
        case TOKEN_TYPE_MINUS: return left_value - right_value;
        case TOKEN_TYPE_ASTERISK: return left_value * right_value;
        case TOKEN_TYPE_SLASH: return left_value / right_value;
        default:
            fprintf(stderr, "Unknown binary operator type %d\n", binary_op_node->operation.type);
            exit(EXIT_FAILURE);
    }
}

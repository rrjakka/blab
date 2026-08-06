#include "include/ast/variable_assignment_node.h"

#include "include/ast/ast_node.h"
#include <stdlib.h>


ast_node_t* variable_assignment_node_new(const string_view_t name, ast_node_t* value)
{
    const auto node = (ast_node_t*)malloc(sizeof(ast_node_t));
    node->type = AST_NODE_VARIABLE_ASSIGNMENT;
    node->node.variable_assignment = (variable_assignment_node_t*)malloc(sizeof(variable_assignment_node_t));
    node->node.variable_assignment->name = name;
    node->node.variable_assignment->value = value;
    return node;
}

void variable_assignment_node_free(variable_assignment_node_t* variable_assignment_node)
{
    free(variable_assignment_node);
}

value_t variable_assignment_node_evaluate(const variable_assignment_node_t* variable_assignment_node, context_t* context)
{
    const value_t value = ast_node_evaluate(variable_assignment_node->value, context);
    context_set(context, variable_assignment_node->name, value);
    return value;
}

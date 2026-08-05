#ifndef PESEC_VARIABLE_NODE_H
#define PESEC_VARIABLE_NODE_H

#include "include/value.h"
#include "include/utils/string_view.h"
#include "include/context.h"

typedef struct AST_NODE_STRUCT ast_node_t;

typedef struct
{
    string_view_t name;
} variable_node_t;

ast_node_t* variable_node_new(string_view_t name);

void variable_node_free(variable_node_t* variable_node);

value_t variable_node_evaluate(const variable_node_t* variable_node, const context_t* context);

#endif // PESEC_VARIABLE_NODE_H

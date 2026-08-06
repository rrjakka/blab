#ifndef PESEC_CONDITION_NODE_H
#define PESEC_CONDITION_NODE_H

#include "include/value.h"
#include "include/utils/string_view.h"
#include "include/context.h"

typedef struct AST_NODE_STRUCT ast_node_t;

typedef struct
{
    ast_node_t *condition;
    ast_node_t *if_body;
    ast_node_t *else_body;
} condition_node_t;

ast_node_t* condition_node_new(ast_node_t *condition, ast_node_t *if_body, ast_node_t *else_body);

void condition_node_free(condition_node_t* condition_node);

value_t condition_node_evaluate(const condition_node_t* condition_node, context_t* context);

#endif // PESEC_CONDITION_NODE_H

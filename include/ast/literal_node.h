#ifndef PESEC_LITERAL_NODE_H
#define PESEC_LITERAL_NODE_H

#include "include/value.h"
#include "include/context.h"

typedef struct AST_NODE_STRUCT ast_node_t;

typedef struct
{
    value_t value;
} literal_node_t;

ast_node_t* literal_node_new(value_t value);

void literal_node_free(literal_node_t* literal_node);

value_t literal_node_evaluate(const literal_node_t* literal_node, context_t* context);

#endif // PESEC_LITERAL_NODE_H

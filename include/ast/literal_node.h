#ifndef BLAB_LITERAL_NODE_H
#define BLAB_LITERAL_NODE_H

#include "include/value.h"

typedef struct AST_NODE_STRUCT ast_node_t;

typedef struct
{
    value_t value;
} literal_node_t;

ast_node_t* literal_node_new(value_t value);

value_t literal_node_evaluate(const literal_node_t* literal_node);

#endif // BLAB_LITERAL_NODE_H

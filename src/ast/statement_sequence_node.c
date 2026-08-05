#include "include/ast/statement_sequence_node.h"

#include "include/ast/ast_node.h"
#include <stdlib.h>

ast_node_t* statement_sequence_node_new(ast_node_t** statements, unsigned long long statements_count)
{
    const auto node = (ast_node_t*)malloc(sizeof(ast_node_t));
    node->type = AST_NODE_STATEMENT_SEQUENCE;
    node->node.statement_sequence = (statement_sequence_node_t*)malloc(sizeof(statement_sequence_node_t));
    node->node.statement_sequence->statements = statements;
    node->node.statement_sequence->statements_count = statements_count;
    return node;
}

void statement_sequence_node_free(statement_sequence_node_t* statement_sequence_node)
{
    free(statement_sequence_node);
}

value_t statement_sequence_node_evaluate(const statement_sequence_node_t* statement_sequence_node, context_t* context)
{
    long double result = 0;

    for (int i = 0; i < statement_sequence_node->statements_count; i++)
    {
        result = ast_node_evaluate(statement_sequence_node->statements[i], context);
    }

    return result;
}

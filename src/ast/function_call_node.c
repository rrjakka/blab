#include "include/ast/function_call_node.h"

#include <stdio.h>

#include "include/ast/ast_node.h"
#include <stdlib.h>


ast_node_t* function_call_node_new(const string_view_t name, ast_node_t* arguments)
{
    const auto node = (ast_node_t*)malloc(sizeof(ast_node_t));
    node->type = AST_NODE_FUNCTION_CALL;
    node->node.function_call = (function_call_node_t*)malloc(sizeof(function_call_node_t));
    node->node.function_call->name = name;
    node->node.function_call->arguments = arguments;
    return node;
}

void function_call_node_free(function_call_node_t* function_call_node)
{
    ast_node_free(function_call_node->arguments);
    free(function_call_node);
}

value_t function_call_node_evaluate(const function_call_node_t* function_call_node, context_t* context)
{
    const statement_sequence_node_queue_t* current = function_call_node->arguments->node.statement_sequence->statements;
    const auto evaluated_values = (value_t*)calloc(function_call_node->arguments->node.statement_sequence->statements_count, sizeof(value_t));

    unsigned long long i = 0;
    while (current)
    {
        evaluated_values[i++] = ast_node_evaluate(current->statement, context);
        current = current->next;
    }

    if (string_view_equals_cstr(function_call_node->name, "println"))
    {
        for (i = 0; i < function_call_node->arguments->node.statement_sequence->statements_count; i++)
        {
            value_print(evaluated_values[i]);
        }
        printf("\n");
    }

    free(evaluated_values);

    return (value_t) {
        .type = VALUE_TYPE_NUMBER,
        .value.as_number = 0,
    };
}

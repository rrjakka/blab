#include "include/ast/function_call_node.h"

#include <stdio.h>

#include "include/ast/ast_node.h"
#include <stdlib.h>
#include <string.h>


ast_node_t* function_call_node_new(const string_view_t name, ast_node_t **arguments, const unsigned long long arguments_count)
{
    const auto node = (ast_node_t*)malloc(sizeof(ast_node_t));
    node->type = AST_NODE_FUNCTION_CALL;
    node->node.function_call = (function_call_node_t*)malloc(sizeof(function_call_node_t));
    node->node.function_call->name = name;
    node->node.function_call->arguments = arguments;
    node->node.function_call->arguments_count = arguments_count;
    return node;
}

void function_call_node_free(function_call_node_t* function_call_node)
{
    for (int i = 0; i < function_call_node->arguments_count; i++)
        ast_node_free(function_call_node->arguments[i]);

    free(function_call_node);
}

value_t function_call_node_evaluate(const function_call_node_t* function_call_node, context_t* context)
{
    const auto evaluated_values = (value_t*)calloc(function_call_node->arguments_count, sizeof(value_t));

    for (int i = 0; i < function_call_node->arguments_count; i++)
        evaluated_values[i] = ast_node_evaluate(function_call_node->arguments[i], context);

    if (memcmp(function_call_node->name.string, "println", function_call_node->name.length) == 0)
    {
        for (int i = 0; i < function_call_node->arguments_count; i++)
        {
            switch (evaluated_values[i].type)
            {
                case VALUE_TYPE_NUMBER:
                    printf("%Lf", evaluated_values[i].value.as_number);
                    break;
                case VALUE_TYPE_STRING:
                    printf("%.*s", evaluated_values[i].value.as_string.length, evaluated_values[i].value.as_string.string);
                    break;
            }
        }
        printf("\n");
    }

    return (value_t) {
        .type = VALUE_TYPE_NUMBER,
        .value.as_number = 0,
    };
}

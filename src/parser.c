#include "include/parser.h"

#include <stdio.h>
#include <stdlib.h>


parser_t* parser_new(lexer_t* lexer)
{
    const auto parser = (parser_t*)malloc(sizeof(parser_t));

    parser->lexer = lexer;
    parser->current_token = lexer_next_token(parser->lexer);

    return parser;
}

bool parser_match(const parser_t* parser, const token_type_t type)
{
    return parser->current_token.type == type;
}

token_t parser_eat(parser_t* parser, const token_type_t type)
{
    if (!parser_match(parser, type))
    {
        fprintf(stderr, "Unexpected token type %d\n", parser->current_token.type);
        exit(EXIT_FAILURE);
    }
    const token_t prev_token = parser->current_token;
    parser->current_token = lexer_next_token(parser->lexer);

    return prev_token;
}

ast_node_t* parser_parse(parser_t* parser)
{
    const auto statements = (ast_node_t**)calloc(256, sizeof(ast_node_t*));
    unsigned long long statements_count = 0;

    while (!parser_match(parser, TOKEN_TYPE_EOF))
    {
        statements[statements_count++] = parser_parse_expression(parser);
        parser_eat(parser, TOKEN_TYPE_SEMICOLON);
    }

    return statement_sequence_node_new(statements, statements_count);
}

ast_node_t* parser_parse_identifier(parser_t* parser)
{
    const string_view_t name = parser_eat(parser, TOKEN_TYPE_IDENTIFIER).value.as_string;

    if (parser_match(parser, TOKEN_TYPE_LPAREN)) return parser_parse_function_call(parser, name);

    return parser_parse_variable(parser, name);
}

ast_node_t* parser_parse_variable(parser_t* parser, const string_view_t name)
{
    return variable_node_new(name);
}

ast_node_t *parser_parse_function_call(parser_t *parser, const string_view_t name)
{
    parser_eat(parser, TOKEN_TYPE_LPAREN);

    if (parser_match(parser, TOKEN_TYPE_RPAREN))
    {
        parser_eat(parser, TOKEN_TYPE_RPAREN);
        return function_call_node_new(name, nullptr, 0);
    }

    const auto args = (ast_node_t**)calloc(256, sizeof(ast_node_t*)); // TODO: dynamically resize array
    unsigned long long arg_count = 0;

    args[arg_count] = parser_parse_expression(parser);
    ++arg_count;

    while (parser_match(parser, TOKEN_TYPE_COMMA))
    {
        parser_eat(parser, TOKEN_TYPE_COMMA);
        args[arg_count] = parser_parse_expression(parser);
        ++arg_count;
    }

    parser_eat(parser, TOKEN_TYPE_RPAREN);

    return function_call_node_new(name, args, arg_count);
}

ast_node_t* parser_parse_expression(parser_t* parser)
{
    ast_node_t* left = parser_parse_term(parser);
    ast_node_t* right = nullptr;

    while (parser_match(parser, TOKEN_TYPE_PLUS) ||
           parser_match(parser, TOKEN_TYPE_MINUS))
    {
        const token_t operation = parser_eat(parser, parser->current_token.type);

        right = parser_parse_term(parser);
        left = binary_op_node_new(operation, left, right);
    }

    return left;
}

ast_node_t* parser_parse_term(parser_t* parser)
{
    ast_node_t* left = parser_parse_factor(parser);
    ast_node_t* right = nullptr;

    while (parser_match(parser, TOKEN_TYPE_ASTERISK) ||
           parser_match(parser, TOKEN_TYPE_SLASH))
    {
        const token_t operation = parser_eat(parser, parser->current_token.type);

        right = parser_parse_factor(parser);
        left = binary_op_node_new(operation, left, right);
    }

    return left;
}

ast_node_t* parser_parse_factor(parser_t* parser)
{
    ast_node_t* node = nullptr;
    switch (parser->current_token.type)
    {
        case TOKEN_TYPE_NUMBER:
            node = literal_node_new(parser_eat(parser, TOKEN_TYPE_NUMBER).value.as_number);
            break;
        case TOKEN_TYPE_IDENTIFIER:
            node = parser_parse_identifier(parser);
            break;
        case TOKEN_TYPE_LPAREN:
            parser_eat(parser, TOKEN_TYPE_LPAREN);
            node = parser_parse_expression(parser);
            parser_eat(parser, TOKEN_TYPE_RPAREN);
            break;
        default:
            break;
    }

    if (!node)
    {
        fprintf(stderr, "Unexpected token type %d\n", parser->current_token.type);
        exit(EXIT_FAILURE);
    }

    return node;
}

void parser_free(parser_t* parser)
{
    free(parser);
}
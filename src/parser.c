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
        fprintf(stderr, "Unexpected token type\n");
        exit(-1);
    }
    const token_t prev_token = parser->current_token;
    parser->current_token = lexer_next_token(parser->lexer);

    return prev_token;
}

ast_node_t* parser_parse(parser_t* parser)
{
    ast_node_t* node = parser_parse_expression(parser);

    if (!parser_match(parser, TOKEN_TYPE_EOF))
    {
        fprintf(stderr, "Unexpected token after expression\n");
        exit(EXIT_FAILURE);
    }

    return node;
}

ast_node_t* parser_parse_variable(parser_t* parser)
{
    const string_view_t name = parser_eat(parser, TOKEN_TYPE_IDENTIFIER).value.as_string;

    return variable_node_new(name);
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
            node = parser_parse_variable(parser);
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
        fprintf(stderr, "Unexpected token type\n");
        exit(EXIT_FAILURE);
    }

    return node;
}

void parser_free(parser_t* parser)
{
    free(parser);
}
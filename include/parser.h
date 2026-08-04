#ifndef BLAB_PARSER_H
#define BLAB_PARSER_H

#include "lexer.h"
#include "ast/ast_node.h"

typedef struct
{
    lexer_t* lexer;
    token_t current_token;
} parser_t;

parser_t* parser_new(lexer_t* lexer);

bool parser_match(const parser_t* parser, token_type_t type);

token_t parser_eat(parser_t* parser, token_type_t type);

ast_node_t* parser_parse(parser_t* parser);

// у отца было три сына

ast_node_t* parser_parse_expression(parser_t* parser); // старший вовсе был детина

ast_node_t* parser_parse_term(parser_t* parser); // средний был ни так ни сяк

ast_node_t* parser_parse_factor(parser_t* parser); // младший был куколд сойджак

void parser_free(parser_t* parser);

#endif// BLAB_PARSER_H
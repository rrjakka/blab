#ifndef PESEC_TOKEN_H
#define PESEC_TOKEN_H

#include "utils/string_view.h"

typedef enum
{
    TOKEN_TYPE_NUMBER,
    TOKEN_TYPE_IDENTIFIER,
    TOKEN_TYPE_STRING,

    TOKEN_TYPE_EQUALS,

    TOKEN_TYPE_PLUS,
    TOKEN_TYPE_MINUS,
    TOKEN_TYPE_SLASH,
    TOKEN_TYPE_ASTERISK,

    TOKEN_TYPE_LPAREN,
    TOKEN_TYPE_RPAREN,

    TOKEN_TYPE_LBRACE,
    TOKEN_TYPE_RBRACE,

    TOKEN_TYPE_LBRACKET,
    TOKEN_TYPE_RBRACKET,

    TOKEN_TYPE_COMMA,
    TOKEN_TYPE_SEMICOLON,

    TOKEN_TYPE_EOF
} token_type_t;

typedef union
{
    string_view_t as_string;
    long double as_number;
} token_value_t;

typedef struct
{
    token_value_t value;
    token_type_t type;
} token_t;

#endif // PESEC_TOKEN_H
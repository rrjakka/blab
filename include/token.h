#ifndef BLAB_TOKEN_H
#define BLAB_TOKEN_H

typedef enum
{
    TOKEN_TYPE_NUMBER,
    TOKEN_TYPE_IDENTIFIER,

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

    TOKEN_TYPE_EOF
} token_type_t;

typedef union
{
    struct
    {
        char* ptr;
        long long length;
    } as_string;
    long double as_number;
} token_value_t;

typedef struct
{
    token_value_t value;
    token_type_t type;
} token_t;

#endif // BLAB_TOKEN_H
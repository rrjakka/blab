#include "include/lexer.h"

#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>


lexer_t* lexer_new(char* source, const unsigned long long length)
{
    const auto lexer = (lexer_t*)malloc(sizeof(lexer_t));

    lexer->source = source;
    lexer->i = 0;
    lexer->length = length;

    return lexer;
}

void lexer_advance(lexer_t* lexer)
{
    if (!lexer_can_advance(lexer))
    {
        fprintf(stderr, "EOF reached, can't advance");
        exit(EXIT_FAILURE);
    }

    lexer->i++;
}

bool lexer_can_advance(const lexer_t* lexer)
{
    return lexer->i < lexer->length;
}

token_t lexer_next_token(lexer_t* lexer)
{
    if (!lexer_can_advance(lexer)) return (token_t){
        .value = (token_value_t){ .as_number = 0 },
        .type = TOKEN_TYPE_EOF,
    };

    char current_char = lexer->source[lexer->i];
    while (lexer_can_advance(lexer) && isspace(current_char = lexer->source[lexer->i])) lexer->i++;

    if (!lexer_can_advance(lexer)) return (token_t){
        .value = nullptr,
        .type = TOKEN_TYPE_EOF
    };

    if (isdigit(current_char) || current_char == '.') return lexer_next_number(lexer);
    if (isalpha(current_char) || current_char == '_') return lexer_next_identifier(lexer);
    if (current_char == '"') return lexer_next_string(lexer);
    switch (current_char)
    {
        case '+': lexer_advance(lexer); return (token_t){ .value = nullptr, .type = TOKEN_TYPE_PLUS };
        case '-': lexer_advance(lexer); return (token_t){ .value = nullptr, .type = TOKEN_TYPE_MINUS };
        case '*': lexer_advance(lexer); return (token_t){ .value = nullptr, .type = TOKEN_TYPE_ASTERISK };
        case '/': lexer_advance(lexer); return (token_t){ .value = nullptr, .type = TOKEN_TYPE_SLASH };
        case ',': lexer_advance(lexer); return (token_t){ .value = nullptr, .type = TOKEN_TYPE_COMMA };
        case ';': lexer_advance(lexer); return (token_t){ .value = nullptr, .type = TOKEN_TYPE_SEMICOLON };
        case '(': lexer_advance(lexer); return (token_t){ .value = nullptr, .type = TOKEN_TYPE_LPAREN };
        case ')': lexer_advance(lexer); return (token_t){ .value = nullptr, .type = TOKEN_TYPE_RPAREN };
        case '{': lexer_advance(lexer); return (token_t){ .value = nullptr, .type = TOKEN_TYPE_LBRACE };
        case '}': lexer_advance(lexer); return (token_t){ .value = nullptr, .type = TOKEN_TYPE_RBRACE };
        case '[': lexer_advance(lexer); return (token_t){ .value = nullptr, .type = TOKEN_TYPE_LBRACKET };
        case ']': lexer_advance(lexer); return (token_t){ .value = nullptr, .type = TOKEN_TYPE_RBRACKET };
        default:
            fprintf(stderr, "Unknown character: '%c'\n", current_char);
            exit(EXIT_FAILURE);
    }
}

token_t lexer_next_number(lexer_t* lexer)
{
    const unsigned long long begin = lexer->i;
    bool has_dot = false;

    while (lexer_can_advance(lexer) && (isdigit(lexer->source[lexer->i]) || lexer->source[lexer->i] == '.'))
    {
        if (lexer->source[lexer->i] == '.')
        {
            if (has_dot)
            {
                fprintf(stderr, "Invalid number");
                exit(EXIT_FAILURE);
            }
            has_dot = true;
        }
        lexer_advance(lexer);
    }

    const unsigned long long buffer_size = lexer->i - begin;
    const auto buffer = (char*)malloc(sizeof(char) * buffer_size + 1);
    memcpy(buffer, lexer->source + begin, buffer_size );
    buffer[buffer_size] = '\0';

    const long double value = strtold(buffer, nullptr);

    free(buffer);

    return (token_t){
        .value.as_number = value,
        .type = TOKEN_TYPE_NUMBER,
    };
}

token_t lexer_next_identifier(lexer_t* lexer)
{
    const unsigned long long begin = lexer->i;

    while (lexer_can_advance(lexer) && (
            isalnum(lexer->source[lexer->i]) ||
            lexer->source[lexer->i] == '#' ||
            lexer->source[lexer->i] == '_'
            )) lexer_advance(lexer);

    return (token_t){
        .value.as_string = {
            .string = lexer->source + begin,
            .length = lexer->i - begin,
        },
        .type = TOKEN_TYPE_IDENTIFIER,
    };
}

token_t lexer_next_string(lexer_t* lexer)
{
    lexer_advance(lexer);
    const unsigned long long begin = lexer->i;

    while (lexer_can_advance(lexer) && lexer->source[lexer->i] != '"') lexer_advance(lexer);

    const unsigned long long length = lexer->i - begin;

    lexer_advance(lexer);

    return (token_t){
        .value.as_string = {
            .string = lexer->source + begin,
            .length = length,
        },
        .type = TOKEN_TYPE_STRING,
    };
}

void lexer_free(lexer_t* lexer)
{
    free(lexer);
}

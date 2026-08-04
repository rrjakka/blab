#ifndef BLAB_LEXER_H
#define BLAB_LEXER_H

#include "token.h"

typedef struct
{
    char* source;
    long long i;
    long long length;
} lexer_t;

lexer_t* lexer_new(char* source, long long length);

void lexer_advance(lexer_t* lexer);

bool lexer_can_advance(const lexer_t* lexer);

token_t lexer_next_token(lexer_t* lexer);

token_t lexer_next_number(lexer_t* lexer);

token_t lexer_next_identifier(lexer_t* lexer);

void lexer_free(lexer_t* lexer);

#endif // BLAB_LEXER_H
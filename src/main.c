#include <stdio.h>
#include <string.h>

#include "include/lexer.h"


int main()
{
    const auto test = "2 + 2 * 2";

    lexer_t* lexer = lexer_new(test, strlen(test));

    parser_t* parser = parser_new(lexer);

    lexer_free(lexer);

    return 0;
}

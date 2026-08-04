#include <stdio.h>
#include <string.h>

#include "include/lexer.h"
#include "include/parser.h"


int main()
{
    const auto source = "2 + 2 * 2";

    lexer_t* lexer = lexer_new(source, strlen(source));
    parser_t* parser = parser_new(lexer);
    const ast_node_t* ast = parser_parse(parser);

    const value_t result = ast_node_evaluate(ast);

    printf("%s = %Lf", source, result);

    lexer_free(lexer);
    parser_free(parser);

    return 0;
}
